#ifndef TC74_H
#define TC74_H

#include <stdint.h>
#include "esp_err.h"

#define TC74_I2C_SDA_IO      6
#define TC74_I2C_SCL_IO      7
#define TC74_I2C_PORT        0
#define TC74_I2C_FREQ_HZ     100000
#define TC74_DEFAULT_ADDR    0x4D // TC74A5

esp_err_t tc74_init(void);
esp_err_t tc74_read_temp(int8_t *temp);
void tc74_task(void *pvParameters);

#endif // TC74_H
