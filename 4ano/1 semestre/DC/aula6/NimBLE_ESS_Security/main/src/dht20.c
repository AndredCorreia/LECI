#include "dht20.h"
#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"

static const char *TAG = "DHT20";
static i2c_master_bus_handle_t s_bus_handle = NULL;
static i2c_master_dev_handle_t s_dev_handle = NULL;

esp_err_t dht20_init(void) {
    if (s_dev_handle != NULL) {
        return ESP_OK;
    }

    i2c_master_bus_config_t bus_config = {
        .i2c_port = DHT20_I2C_PORT,
        .sda_io_num = DHT20_I2C_SDA_IO,
        .scl_io_num = DHT20_I2C_SCL_IO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    esp_err_t err = i2c_new_master_bus(&bus_config, &s_bus_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize I2C bus: %s", esp_err_to_name(err));
        return err;
    }

    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = DHT20_I2C_ADDR,
        .scl_speed_hz = DHT20_I2C_FREQ_HZ,
    };

    err = i2c_master_bus_add_device(s_bus_handle, &dev_config, &s_dev_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to add DHT20 device to bus: %s", esp_err_to_name(err));
        return err;
    }

    ESP_LOGI(TAG, "DHT20 I2C master initialized (SDA=%d, SCL=%d, addr=0x%02X)",
             DHT20_I2C_SDA_IO, DHT20_I2C_SCL_IO, DHT20_I2C_ADDR);

    vTaskDelay(pdMS_TO_TICKS(100)); // Power-up stabilization
    return ESP_OK;
}

esp_err_t dht20_read(float *temperature, float *humidity) {
    if (s_dev_handle == NULL) {
        esp_err_t init_ret = dht20_init();
        if (init_ret != ESP_OK) {
            return init_ret;
        }
    }

    uint8_t cmd[3] = {0xAC, 0x33, 0x00};
    uint8_t data[7] = {0};

    // 1. Send measurement trigger
    esp_err_t err = i2c_master_transmit(s_dev_handle, cmd, sizeof(cmd), pdMS_TO_TICKS(100));
    if (err != ESP_OK) {
        return err;
    }

    // 2. Wait for measurement conversion (80 ms)
    vTaskDelay(pdMS_TO_TICKS(80));

    // 3. Read 7 bytes
    err = i2c_master_receive(s_dev_handle, data, sizeof(data), pdMS_TO_TICKS(100));
    if (err != ESP_OK) {
        return err;
    }

    // 4. Check status bit 7 (0: ready, 1: busy)
    if ((data[0] & 0x80) == 0) {
        uint32_t hum_raw = ((uint32_t)data[1] << 12) |
                           ((uint32_t)data[2] << 4) |
                           ((data[3] & 0xF0) >> 4);
        *humidity = ((float)hum_raw / 1048576.0f) * 100.0f;

        uint32_t temp_raw = (((uint32_t)(data[3] & 0x0F)) << 16) |
                            ((uint32_t)data[4] << 8) |
                            data[5];
        *temperature = (((float)temp_raw / 1048576.0f) * 200.0f) - 50.0f;

        return ESP_OK;
    }

    return ESP_ERR_INVALID_STATE; // Sensor busy
}
