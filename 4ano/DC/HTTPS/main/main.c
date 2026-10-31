/* Simple HTTP + SSL Server Example with DHT20 in SoftAP Mode */

#include <string.h>
#include <unistd.h>
#include <esp_event.h>
#include <esp_log.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"

#include <esp_https_server.h>
#include "esp_tls.h"
#include "esp_key_config.h"
#include "sdkconfig.h"

// Driver moderno I2C
#include "driver/i2c_master.h"

#if CONFIG_EXAMPLE_ENABLE_HTTPS_SERVER_CUSTOM_CIPHERSUITES
#include "mbedtls/ssl_ciphersuites.h"
#endif

static const char *TAG = "example";

// Definições do SoftAP (nome e password da rede gerada pela placa)
#define EXAMPLE_ESP_WIFI_SSID      "ssid"
#define EXAMPLE_ESP_WIFI_PASS      "password"
#define EXAMPLE_ESP_WIFI_CHANNEL   1
#define EXAMPLE_MAX_STA_CONN       4

// Pinos I2C e endereço do DHT20 (Tabela 7)
#define I2C_MASTER_SDA_IO           6    
#define I2C_MASTER_SCL_IO           7    
#define I2C_MASTER_NUM              I2C_NUM_0
#define DHT20_SENSOR_ADDR           0x38

static i2c_master_dev_handle_t dht20_handle = NULL;
static httpd_handle_t server = NULL;

// Inicialização do barramento I2C e do sensor DHT20
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
        .device_address = DHT20_SENSOR_ADDR,
        .scl_speed_hz = 100000,
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dht20_handle));
    ESP_LOGI(TAG, "Sensor DHT20 inicializado com sucesso no SDA=%d, SCL=%d.", I2C_MASTER_SDA_IO, I2C_MASTER_SCL_IO);
}

// Leitura do DHT20 corrigida (comando de 3 bytes + atraso de ~80ms)
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

/* Handler da rota / */
static esp_err_t root_get_handler(httpd_req_t *req)
{
    float temperature = 0.0;
    float humidity = 0.0;

    if (read_dht20(&temperature, &humidity) != ESP_OK) {
        ESP_LOGW(TAG, "Falha na leitura do sensor DHT20!");
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Erro ao ler o sensor DHT20");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Pedido na rota / | Temperatura: %.1f °C | Humidade: %.1f %%", temperature, humidity);

    char resp_str[256];
    snprintf(resp_str, sizeof(resp_str), 
             "<html><body>"
             "<h1>Sensor DHT20 - ESP32-C6 (SoftAP)</h1>"
             "<p>Temperatura: %.1f &deg;C</p>"
             "<p>Humidade: %.1f %%</p>"
             "</body></html>", 
             temperature, humidity);

    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, resp_str, HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}

static const httpd_uri_t root = {
    .uri     = "/",
    .method  = HTTP_GET,
    .handler = root_get_handler
};

static httpd_handle_t start_webserver(void)
{
    httpd_handle_t srv = NULL;
    ESP_LOGI(TAG, "Starting server");
    httpd_ssl_config_t conf = HTTPD_SSL_CONFIG_DEFAULT();

    extern const unsigned char servercert_start[] asm("_binary_servercert_pem_start");
    extern const unsigned char servercert_end[]   asm("_binary_servercert_pem_end");
    extern const unsigned char cacert_start[] asm("_binary_cacert_pem_start");
    extern const unsigned char cacert_end[]   asm("_binary_cacert_pem_end");
    
    conf.servercert = servercert_start;
    conf.servercert_len = servercert_end - servercert_start;
    conf.cacert_pem = cacert_start;
    conf.cacert_len = cacert_end - cacert_start;

#if CONFIG_EXAMPLE_ENABLE_SKIP_CLIENT_CERT
    conf.client_cert_authmode_optional = true;
#endif

    extern const unsigned char prvtkey_pem_start[] asm("_binary_prvtkey_pem_start");
    extern const unsigned char prvtkey_pem_end[]   asm("_binary_prvtkey_pem_end");
    
    static esp_key_config_t server_key = {
        .source = ESP_KEY_SOURCE_BUFFER,
        .buffer = {
            .data = prvtkey_pem_start,
        }
    };
    server_key.buffer.len = prvtkey_pem_end - prvtkey_pem_start;
    conf.server_key = &server_key;

    esp_err_t ret = httpd_ssl_start(&srv, &conf);
    if (ESP_OK != ret) {
        ESP_LOGI(TAG, "Error starting server!");
        return NULL;
    }

    ESP_LOGI(TAG, "Registering URI handlers");
    httpd_register_uri_handler(srv, &root);
    return srv;
}

// Event Handler para o SoftAP e atribuição de IP aos clientes
static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_START) {
        ESP_LOGI(TAG, "SoftAP iniciado com sucesso. A arrancar servidor HTTPS...");
        if (server == NULL) {
            server = start_webserver();
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_AP_STAIPASSIGNED) {
        ip_event_ap_staipassigned_t *event = (ip_event_ap_staipassigned_t *) event_data;
        char ip_str[IP4ADDR_STRLEN_MAX];
        esp_ip4addr_ntoa(&event->ip, ip_str, sizeof(ip_str));
        ESP_LOGI(TAG, "Endereço IP atribuído ao cliente conectado: %s", ip_str);
    }
}

// Inicialização do modo SoftAP
static void wifi_init_softap(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_AP_STAIPASSIGNED,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .ssid_len = strlen(EXAMPLE_ESP_WIFI_SSID),
            .channel = EXAMPLE_ESP_WIFI_CHANNEL,
            .password = EXAMPLE_ESP_WIFI_PASS,
            .max_connection = EXAMPLE_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA2_PSK,
        },
    };
    if (strlen(EXAMPLE_ESP_WIFI_PASS) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s channel:%d",
             EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS, EXAMPLE_ESP_WIFI_CHANNEL);
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());

    // Inicializa o sensor DHT20
    init_dht20();

    // Inicializa o Wi-Fi em modo SoftAP (substitui o example_connect())
    wifi_init_softap();
}