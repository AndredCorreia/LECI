#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <stdint.h>
#include <stdbool.h>

#define SENSOR_TEMP_UNKNOWN 0x8000  // Table 8: int16 -32768
#define SENSOR_HUM_UNKNOWN  0xFFFF  // Table 8: uint16 65535

#ifdef __cplusplus
extern "C" {
#endif

void sensor_data_init(void);
void sensor_data_update(int16_t temp_sint16, uint16_t hum_uint16);
void sensor_data_get(int16_t *temp_sint16, uint16_t *hum_uint16);

uint16_t get_sampling_period(void);
void set_sampling_period(uint16_t period_s);

void acquisition_task(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif // SENSOR_DATA_H
