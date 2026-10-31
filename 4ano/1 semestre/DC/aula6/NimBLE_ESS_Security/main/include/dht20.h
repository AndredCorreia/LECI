#ifndef DHT20_H
#define DHT20_H

#include "esp_err.h"

#define DHT20_I2C_SDA_IO      6
#define DHT20_I2C_SCL_IO      7
#define DHT20_I2C_PORT        0
#define DHT20_I2C_FREQ_HZ     100000
#define DHT20_I2C_ADDR        0x38

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t dht20_init(void);
esp_err_t dht20_read(float *temperature, float *humidity);

#ifdef __cplusplus
}
#endif

#endif // DHT20_H
