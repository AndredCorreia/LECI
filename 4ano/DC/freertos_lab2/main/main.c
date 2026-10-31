#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static TaskHandle_t receiverHandler = NULL;

void sender(void *params)
{
    while (true)
    {
        // Envia os diferentes valores numéricos com pausas entre eles
        xTaskNotify(receiverHandler, 1, eSetValueWithOverwrite);
        vTaskDelay(pdMS_TO_TICKS(1000));

        xTaskNotify(receiverHandler, 2, eSetValueWithOverwrite);
        vTaskDelay(pdMS_TO_TICKS(1000));

        xTaskNotify(receiverHandler, 4, eSetValueWithOverwrite);
        vTaskDelay(pdMS_TO_TICKS(1000));

        xTaskNotify(receiverHandler, 8, eSetValueWithOverwrite);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void receiver(void *params)
{
    uint32_t notified_value = 0;

    while (true)
    {
        // Aguarda pela notificação e extrai o valor numérico recebido para 'notified_value'
        if (xTaskNotifyWait(0x00, 0xFFFFFFFF, &notified_value, portMAX_DELAY) == pdTRUE)
        {
            printf("-$ received notification %lu\n", (unsigned long)notified_value);
            fflush(stdout);
        }
    }
}

void app_main(void)
{
    xTaskCreate(&receiver, "receiver", 2048, NULL, 2, &receiverHandler);
    xTaskCreate(&sender, "sender", 2048, NULL, 2, NULL);
}