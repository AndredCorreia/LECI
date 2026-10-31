#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/spi_master.h"
#include "dht20.h"
#include "battery.h" // O teu componente da bateria

static const char *TAG = "ECO_MAIN";

#define MOUNT_POINT "/sdcard"

#define PIN_NUM_MISO  CONFIG_EXAMPLE_PIN_MISO
#define PIN_NUM_MOSI  CONFIG_EXAMPLE_PIN_MOSI
#define PIN_NUM_CLK   CONFIG_EXAMPLE_PIN_CLK
#define PIN_NUM_CS    CONFIG_EXAMPLE_PIN_CS

// Estrutura atualizada para incluir a bateria
typedef struct {
    float temperatura;
    float humidade;
    int tensao_mv; // Novo campo para a tensão em milivolts
} sensor_data_t;

static QueueHandle_t sensor_queue = NULL;
static adc_oneshot_unit_handle_t adc1_handle; // Handle do ADC do componente

// Tarefa Produtora: Lê o DHT20 e a Bateria
static void dht20_task(void *pvParameters)
{
    i2c_master_bus_handle_t bus_handle;
    i2c_master_dev_handle_t dev_handle;

    ESP_LOGI(TAG, "A inicializar o sensor DHT20 na tarefa...");
    dht20_init(&bus_handle, &dev_handle);

    sensor_data_t data;

    while (1) {
        // 1. Lê o sensor DHT20
        esp_err_t err = dht20_read(dev_handle, &data.temperatura, &data.humidade);
        
        // 2. Lê a tensão da bateria usando a função do teu componente
        data.tensao_mv = battery_read_mv(adc1_handle);
        
        if (err == ESP_OK) {
            ESP_LOGI(TAG, "Temp: %.2f ºC | Hum: %.2f %% | Bat: %d mV", 
                     data.temperatura, data.humidade, data.tensao_mv);
            
            if (xQueueSend(sensor_queue, &data, pdMS_TO_TICKS(100)) != pdPASS) {
                ESP_LOGW(TAG, "Aviso: Fila cheia, dado descartado.");
            }
        } else {
            ESP_LOGW(TAG, "Erro ao ler o DHT20 ou sensor ocupado.");
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Tarefa Consumidora: Grava Temp, Humidade e Bateria no CSV
static void logger_task(void *pvParameters)
{
    sensor_data_t received_data;

    while (1) {
        if (xQueueReceive(sensor_queue, &received_data, portMAX_DELAY) == pdTRUE) {
            
            FILE *f = fopen(MOUNT_POINT "/dht20_log.csv", "a");
            if (f == NULL) {
                ESP_LOGE("LOGGER", "Falha ao abrir o ficheiro CSV!");
                continue;
            }

            // Grava os 3 valores separados por vírgula no CSV
            fprintf(f, "%.2f,%.2f,%d\n", 
                    received_data.temperatura, 
                    received_data.humidade, 
                    received_data.tensao_mv);
            fclose(f);

            ESP_LOGI("LOGGER", "Guardado no SD -> Temp: %.2f ºC, Hum: %.2f %%, Bat: %d mV", 
                     received_data.temperatura, received_data.humidade, received_data.tensao_mv);
        }
    }
}

void app_main(void)
{
    esp_err_t ret;

    ESP_LOGI(TAG, "A inicializar o sistema EcoNode...");

    // Inicializa o componente da Bateria (ADC)
    battery_init(&adc1_handle);

    // Configuração e montagem do Cartão SD por SPI
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
#ifdef CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .format_if_mount_failed = true,
#else
        .format_if_mount_failed = false,
#endif
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };
    
    sdmmc_card_t *card;
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();

    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };

    ret = spi_bus_initialize(host.slot, &bus_cfg, SDSPI_DEFAULT_DMA);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Falha ao inicializar o barramento SPI do SD.");
        return;
    }

    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_CS;
    slot_config.host_id = host.slot;

    ret = esp_vfs_fat_sdspi_mount(MOUNT_POINT, &host, &slot_config, &mount_config, &card);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Falha ao montar o cartão SD.");
        return;
    }
    
    ESP_LOGI(TAG, "Cartão SD montado com sucesso!");

    sensor_queue = xQueueCreate(10, sizeof(sensor_data_t));
    if (sensor_queue == NULL) {
        ESP_LOGE(TAG, "Erro ao criar a Queue!");
        return;
    }

    xTaskCreate(dht20_task, "dht20_task", 4096, NULL, 5, NULL);
    xTaskCreate(logger_task, "logger_task", 4096, NULL, 4, NULL);
}