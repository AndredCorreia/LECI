#include "sensor_data.h"
#include <stdio.h>
#include <math.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "dht20.h"
#include "gatt_svc.h"

static const char *TAG = "SENSOR_DATA";

typedef struct {
    int16_t temp_sint16;
    uint16_t hum_uint16;
    bool valid;
} sensor_sample_t;

static sensor_sample_t s_sample = {
    .temp_sint16 = (int16_t)SENSOR_TEMP_UNKNOWN,
    .hum_uint16 = SENSOR_HUM_UNKNOWN,
    .valid = false,
};

static uint16_t s_sampling_period_s = 2; // Default 2 seconds
static SemaphoreHandle_t s_sensor_mutex = NULL;

void sensor_data_init(void) {
    if (s_sensor_mutex == NULL) {
        s_sensor_mutex = xSemaphoreCreateMutex();
    }
}

void sensor_data_update(int16_t temp_sint16, uint16_t hum_uint16) {
    if (s_sensor_mutex == NULL) {
        sensor_data_init();
    }
    if (xSemaphoreTake(s_sensor_mutex, portMAX_DELAY) == pdTRUE) {
        s_sample.temp_sint16 = temp_sint16;
        s_sample.hum_uint16 = hum_uint16;
        s_sample.valid = true;
        xSemaphoreGive(s_sensor_mutex);
    }
}

void sensor_data_get(int16_t *temp_sint16, uint16_t *hum_uint16) {
    if (s_sensor_mutex == NULL) {
        sensor_data_init();
    }
    if (xSemaphoreTake(s_sensor_mutex, portMAX_DELAY) == pdTRUE) {
        *temp_sint16 = s_sample.temp_sint16;
        *hum_uint16 = s_sample.hum_uint16;
        xSemaphoreGive(s_sensor_mutex);
    } else {
        *temp_sint16 = (int16_t)SENSOR_TEMP_UNKNOWN;
        *hum_uint16 = SENSOR_HUM_UNKNOWN;
    }
}

uint16_t get_sampling_period(void) {
    uint16_t period = 2;
    if (s_sensor_mutex == NULL) {
        sensor_data_init();
    }
    if (xSemaphoreTake(s_sensor_mutex, portMAX_DELAY) == pdTRUE) {
        period = s_sampling_period_s;
        xSemaphoreGive(s_sensor_mutex);
    }
    return period;
}

void set_sampling_period(uint16_t period_s) {
    if (s_sensor_mutex == NULL) {
        sensor_data_init();
    }
    if (xSemaphoreTake(s_sensor_mutex, portMAX_DELAY) == pdTRUE) {
        s_sampling_period_s = period_s;
        xSemaphoreGive(s_sensor_mutex);
    }
}

void acquisition_task(void *pvParameters) {
    ESP_LOGI(TAG, "Sensor acquisition task started");
    sensor_data_init();
    esp_err_t err = dht20_init();
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "DHT20 initialization failed (%s). If hardware is not connected, 'unknown' values are reported.",
                 esp_err_to_name(err));
    }

    while (1) {
        uint16_t period = get_sampling_period();
        vTaskDelay(pdMS_TO_TICKS(period * 1000));

        float temp_c = 0.0f;
        float hum_pct = 0.0f;
        err = dht20_read(&temp_c, &hum_pct);

        if (err == ESP_OK) {
            int16_t temp_sint16 = (int16_t)roundf(temp_c * 100.0f);
            uint16_t hum_uint16 = (uint16_t)roundf(hum_pct * 100.0f);

            // 1. Store measurement protected by mutex
            sensor_data_update(temp_sint16, hum_uint16);

            ESP_LOGI(TAG, "DHT20 valid measurement: Temp=%.2f C (%d), Hum=%.2f %% (%u)",
                     temp_c, temp_sint16, hum_pct, hum_uint16);

            // 2. Notify characteristics (after releasing mutex)
            gatt_svr_notify_sensor_data();
        } else {
            ESP_LOGW(TAG, "DHT20 read failed (%s)! Maintaining last valid values.",
                     esp_err_to_name(err));
        }
    }
}
