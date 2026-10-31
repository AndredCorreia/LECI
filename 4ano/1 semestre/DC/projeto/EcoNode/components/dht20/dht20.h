#ifndef DHT20_H
#define DHT20_H

#include "esp_err.h"
#include "driver/i2c_master.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inicializa o barramento I2C e adiciona o sensor DHT20.
 * 
 * @param bus_handle Ponteiro para guardar o handle do barramento I2C.
 * @param dev_handle Ponteiro para guardar o handle do dispositivo DHT20.
 */
void dht20_init(i2c_master_bus_handle_t *bus_handle, i2c_master_dev_handle_t *dev_handle);

/**
 * @brief Lê a temperatura e a humidade do sensor DHT20.
 * 
 * @param dev_handle Handle do dispositivo DHT20.
 * @param temperature Ponteiro para a variável onde será guardada a temperatura (°C).
 * @param humidity Ponteiro para a variável onde será guardada a humidade relativa (%).
 * @return esp_err_t ESP_OK em caso de sucesso, ou código de erro em caso de falha.
 */
esp_err_t dht20_read(i2c_master_dev_handle_t dev_handle, float *temperature, float *humidity);

#ifdef __cplusplus
}
#endif

#endif // DHT20_H