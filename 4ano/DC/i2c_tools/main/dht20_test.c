#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c_master.h"

static const char *TAG = "DHT20";

/* ---- I2C configuration ---- */
#define I2C_MASTER_SCL_IO           7      
#define I2C_MASTER_SDA_IO           6      
#define I2C_MASTER_NUM              I2C_NUM_0
#define I2C_MASTER_FREQ_HZ          100000 
#define I2C_MASTER_TIMEOUT_MS       1000

/* ---- DHT20 specifics ---- */
#define DHT20_ADDR                  0x38

/* ---- I2C bus/device initialization ---- */
static void i2c_master_init(i2c_master_bus_handle_t *bus_handle, i2c_master_dev_handle_t *dev_handle)
{
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_MASTER_NUM,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, bus_handle));

    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = DHT20_ADDR,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ,
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(*bus_handle, &dev_config, dev_handle));
}

void app_main(void)
{
    i2c_master_bus_handle_t bus_handle;
    i2c_master_dev_handle_t dev_handle;

    i2c_master_init(&bus_handle, &dev_handle);
    ESP_LOGI(TAG, "I2C initialized successfully");

    // Espera inicial recomendada de 100ms após o sensor receber energia
    vTaskDelay(pdMS_TO_TICKS(100));

    uint8_t cmd[3] = {0xAC, 0x33, 0x00}; // Comando de trigger
    uint8_t data[7];                     // Buffer para os 7 bytes

    while (1) {
        // 1. Enviar comando de início de medição
        ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, cmd, sizeof(cmd), I2C_MASTER_TIMEOUT_MS));

        // 2. Esperar tempo de processamento do sensor (80 ms)
        vTaskDelay(pdMS_TO_TICKS(80));

        // 3. Ler os 7 bytes resultantes
        ESP_ERROR_CHECK(i2c_master_receive(dev_handle, data, sizeof(data), I2C_MASTER_TIMEOUT_MS));

        // 4. Verificar se o sensor está pronto (Bit 7 do Byte 0 deve ser 0)
        if ((data[0] & 0x80) == 0) {
            
            // Reconstrução dos 20 bits da Humidade
            uint32_t hum_raw = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | ((data[3] & 0xF0) >> 4);
            float humidade = ((float)hum_raw / 1048576.0f) * 100.0f; // 1048576 = 2^20

            // Reconstrução dos 20 bits da Temperatura
            uint32_t temp_raw = (((uint32_t)(data[3] & 0x0F)) << 16) | ((uint32_t)data[4] << 8) | data[5];
            float temperatura = (((float)temp_raw / 1048576.0f) * 200.0f) - 50.0f;

            // Imprimir no terminal com 2 casas decimais, tal como no guião
            ESP_LOGI(TAG, "Temperatura: %.2f C, Humidade: %.2f %%", temperatura, humidade);
        } else {
            ESP_LOGW(TAG, "Aviso: Sensor ocupado.");
        }

        // Intervalo de 2 segundos entre leituras
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}