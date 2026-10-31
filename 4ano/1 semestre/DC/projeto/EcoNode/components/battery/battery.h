#pragma once

#include "esp_err.h"
#include "esp_adc/adc_oneshot.h"

// Função para inicializar a unidade e o canal do ADC
void battery_init(adc_oneshot_unit_handle_t *ret_handle);

// Função para ler a tensão atual em milivolts (mV)
int battery_read_mv(adc_oneshot_unit_handle_t handle);