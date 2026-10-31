#include "tc74.h"
#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "gap.h"
#include "host/ble_hs.h"

static const char *TAG = "TC74";
static i2c_master_bus_handle_t s_bus_handle = NULL;
static i2c_master_dev_handle_t s_dev_handle = NULL;

esp_err_t tc74_init(void) {
    i2c_master_bus_config_t bus_config = {
        .i2c_port = TC74_I2C_PORT,
        .sda_io_num = TC74_I2C_SDA_IO,
        .scl_io_num = TC74_I2C_SCL_IO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    esp_err_t err = i2c_new_master_bus(&bus_config, &s_bus_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize I2C master bus: %s", esp_err_to_name(err));
        return err;
    }

    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = TC74_DEFAULT_ADDR,
        .scl_speed_hz = TC74_I2C_FREQ_HZ,
    };

    err = i2c_master_bus_add_device(s_bus_handle, &dev_config, &s_dev_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to add TC74 device to bus: %s", esp_err_to_name(err));
        return err;
    }

    ESP_LOGI(TAG, "TC74 initialized successfully on SDA=%d, SCL=%d, addr=0x%02X",
             TC74_I2C_SDA_IO, TC74_I2C_SCL_IO, TC74_DEFAULT_ADDR);
    return ESP_OK;
}

esp_err_t tc74_read_temp(int8_t *temp) {
    if (s_dev_handle == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    uint8_t reg = 0x00; // Temperature register
    uint8_t raw = 0;
    esp_err_t err = i2c_master_transmit_receive(s_dev_handle, &reg, 1, &raw, 1, pdMS_TO_TICKS(100));
    if (err == ESP_OK) {
        *temp = (int8_t)raw;
    }
    return err;
}

void tc74_task(void *pvParameters) {
    ESP_LOGI(TAG, "TC74 acquisition task started (period = 2s)");
    
    // Initialise I2C master driver
    esp_err_t init_err = tc74_init();
    if (init_err != ESP_OK) {
        ESP_LOGW(TAG, "TC74 init error (%s). Default mock temperature will be used if hardware is not connected.",
                 esp_err_to_name(init_err));
    }

    int8_t last_temp = 25; // Default valid temperature

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(2000));

        int8_t current_temp = last_temp;
        esp_err_t err = tc74_read_temp(&current_temp);
        if (err == ESP_OK) {
            last_temp = current_temp;
            ESP_LOGI(TAG, "TC74 read successful: %d C", (int)current_temp);
        } else {
            ESP_LOGW(TAG, "TC74 read failed (%s)! Maintaining last advertised value: %d C",
                     esp_err_to_name(err), (int)last_temp);
        }

        // Only update advertisements once the BLE host is synced
        if (ble_hs_synced()) {
            gap_update_temperature(last_temp);
        } else {
            ESP_LOGD(TAG, "NimBLE host not yet synced, skipping advertisement update");
        }
    }
}
