#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "driver/i2c_master.h"
#include "driver/gpio.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

static const char *TAG = "sdlog";

// Configurações do I2C e DHT20
#define I2C_MASTER_NUM     I2C_NUM_0
#define I2C_MASTER_SDA_IO  6
#define I2C_MASTER_SCL_IO  7
#define I2C_MASTER_FREQ_HZ 100000
#define DHT20_ADDR         0x38

// Configurações do Botão BOOT
#define BOOT_BUTTON_PIN    GPIO_NUM_9

// Estrutura de dados partilhada na Queue
typedef struct {
    int64_t millis;
    uint32_t counter;
    float temperature;
    float humidity;
} sample_t;

static i2c_master_dev_handle_t dht20_handle = NULL;
static QueueHandle_t sample_queue = NULL;
static sdmmc_card_t *card = NULL; // CORRIGIDO: tipo correto sdmmc_card_t
static const char *mount_point = "/sdcard";

// Inicialização do barramento I2C e do DHT20
static void init_dht20(void)
{
    i2c_master_bus_config_t i2c_mst_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_MASTER_NUM,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    i2c_master_bus_handle_t bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = DHT20_ADDR,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ,
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dht20_handle));
    ESP_LOGI(TAG, "I2C initialized successfully for DHT20");
}

// Leitura do DHT20 com o driver moderno i2c_master.h
static esp_err_t read_dht20(float *temperature, float *humidity)
{
    uint8_t cmd[3] = {0xAC, 0x33, 0x00};
    uint8_t data[7];

    esp_err_t err = i2c_master_transmit(dht20_handle, cmd, 3, pdMS_TO_TICKS(1000));
    if (err != ESP_OK) return err;

    vTaskDelay(pdMS_TO_TICKS(80));

    err = i2c_master_receive(dht20_handle, data, 7, pdMS_TO_TICKS(1000));
    if (err != ESP_OK) return err;

    uint32_t raw_humidity = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | (data[3] >> 4);
    *humidity = (float)raw_humidity * 100.0 / 1048576.0;

    uint32_t raw_temperature = (((uint32_t)data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | data[5];
    *temperature = (float)raw_temperature * 200.0 / 1048576.0 - 50.0;

    return ESP_OK;
}

// Tarefa Produtora: Sensor DHT20 (Período rigoroso de 1000 ms)
static void sensor_task(void *arg)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(1000);
    xLastWakeTime = xTaskGetTickCount();
    uint32_t counter = 0;

    while (true) {
        float temp = 0.0, hum = 0.0;
        int64_t millis_val = esp_timer_get_time() / 1000;

        esp_err_t err = read_dht20(&temp, &hum);
        if (err == ESP_OK) {
            sample_t sample = {
                .millis = millis_val,
                .counter = counter,
                .temperature = temp,
                .humidity = hum
            };

            if (xQueueSend(sample_queue, &sample, 0) != pdPASS) {
                ESP_LOGW(TAG, "Queue cheia! Amostra descartada.");
            }
        } else {
            ESP_LOGW(TAG, "Falha na leitura do DHT20. Erro: %s", esp_err_to_name(err));
        }

        counter++;

        if (xTaskDelayUntil(&xLastWakeTime, xFrequency) == pdFALSE) {
            ESP_LOGW(TAG, "Período de 1000 ms excedido na tarefa do sensor!");
        }
    }
}

// Tarefa Consumidora: Logging para o Cartão SD
static void logging_task(void *arg)
{
    sample_t sample;
    char file_path[64];
    snprintf(file_path, sizeof(file_path), "%s/dht20.csv", mount_point);

    struct stat st;
    bool file_exists = (stat(file_path, &st) == 0);

    FILE *f = fopen(file_path, "a");
    if (f == NULL) {
        ESP_LOGE(TAG, "Erro ao abrir o ficheiro para escrita: %s (%s)", file_path, strerror(errno));
        vTaskDelete(NULL);
    }
    if (!file_exists) {
        fprintf(f, "millis,counter,temp_C,hum_pct\n");
    }
    fclose(f);

    while (true) {
        if (xQueueReceive(sample_queue, &sample, pdMS_TO_TICKS(100)) == pdPASS) {
            FILE *file = fopen(file_path, "a");
            if (file != NULL) {
                fprintf(file, "%lld,%lu,%.2f,%.2f\n", sample.millis, sample.counter, sample.temperature, sample.humidity);
                fclose(file);
                ESP_LOGI(TAG, "Logged: time=%lld ms, counter=%lu, temp=%.2fC, hum=%.2f%%",
                         sample.millis, sample.counter, sample.temperature, sample.humidity);
            } else {
                ESP_LOGE(TAG, "Erro ao abrir ficheiro no registo: %s", strerror(errno));
            }
        } else {
            if (gpio_get_level(BOOT_BUTTON_PIN) == 0) {
                ESP_LOGI(TAG, "Botão BOOT premido. A terminar logging e a desmontar o cartão...");
                vTaskDelay(pdMS_TO_TICKS(200));
                break;
            }
        }
    }

    esp_vfs_fat_sdcard_unmount(mount_point, card);
    ESP_LOGI(TAG, "Cartão desmontado. Pode remover o cartão.");
    vTaskDelete(NULL);
}

void app_main(void)
{
    // Configurar botão BOOT como entrada com pull-up interno (CORRIGIDO)
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BOOT_BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    ESP_LOGI(TAG, "Initializing SD card");
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = 19,
        .miso_io_num = 20,
        .sclk_io_num = 21,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    ESP_ERROR_CHECK(spi_bus_initialize(host.slot, &bus_cfg, SDSPI_DEFAULT_DMA));

    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = 18;
    slot_config.host_id = host.slot;

    esp_err_t ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to mount filesystem. Error: %s", esp_err_to_name(ret));
        return;
    }
    ESP_LOGI(TAG, "Mounted. Card: %s", card->cid.name);

    init_dht20();

    sample_queue = xQueueCreate(10, sizeof(sample_t));
    if (sample_queue == NULL) {
        ESP_LOGE(TAG, "Erro ao criar a queue!");
        return;
    }

    xTaskCreate(sensor_task, "sensor_task", 4096, NULL, 5, NULL);
    xTaskCreate(logging_task, "logging_task", 4096, NULL, 4, NULL);
}