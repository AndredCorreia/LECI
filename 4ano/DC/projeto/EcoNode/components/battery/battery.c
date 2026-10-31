#include "battery.h"
#include "esp_log.h"

static const char *TAG = "BATTERY_COMP";

#define BATTERY_ADC_UNIT     ADC_UNIT_1
#define BATTERY_ADC_CHANNEL  ADC_CHANNEL_0 

void battery_init(adc_oneshot_unit_handle_t *ret_handle)
{
    adc_oneshot_unit_init_config_t init_config1 = {
        .unit_id = BATTERY_ADC_UNIT,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, ret_handle));

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12, // Atenção de 12dB para cobrir até ~3.3V / 3.9V
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(*ret_handle, BATTERY_ADC_CHANNEL, &config));
    
    ESP_LOGI(TAG, "Componente da bateria inicializado com sucesso.");
}

int battery_read_mv(adc_oneshot_unit_handle_t handle)
{
    int adc_raw = 0;
    esp_err_t err = adc_oneshot_read(handle, BATTERY_ADC_CHANNEL, &adc_raw);
    
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "Erro ao ler o ADC da bateria.");
        return -1;
    }

    // Conversão linear básica para milivolts (baseada num fundo de escala de 3300mV)
    int tensao_mv = (adc_raw * 3300) / 4095;
    return tensao_mv;
}