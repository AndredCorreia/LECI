/*
 * SPDX-FileCopyrightText: 2024-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
/* Includes */
#include "gatt_svc.h"
#include "common.h"
#include "sensor_data.h"
#include "led.h"

/* Private function declarations */
static int temp_chr_access(uint16_t conn_handle, uint16_t attr_handle,
                           struct ble_gatt_access_ctxt *ctxt, void *arg);
static int humidity_chr_access(uint16_t conn_handle, uint16_t attr_handle,
                               struct ble_gatt_access_ctxt *ctxt, void *arg);
static int period_chr_access(uint16_t conn_handle, uint16_t attr_handle,
                             struct ble_gatt_access_ctxt *ctxt, void *arg);
static int passkey_chr_access(uint16_t conn_handle, uint16_t attr_handle,
                              struct ble_gatt_access_ctxt *ctxt, void *arg);
static int led_chr_access(uint16_t conn_handle, uint16_t attr_handle,
                          struct ble_gatt_access_ctxt *ctxt, void *arg);

/* Private variables */
/* 1. Environmental Sensing Service (ESS - 0x181A) */
static const ble_uuid16_t ess_svc_uuid = BLE_UUID16_INIT(0x181A);

static uint16_t temp_chr_val_handle;
static const ble_uuid16_t temp_chr_uuid = BLE_UUID16_INIT(0x2A6E);

static uint16_t humidity_chr_val_handle;
static const ble_uuid16_t humidity_chr_uuid = BLE_UUID16_INIT(0x2A6F);

/* 2. Automation IO service (0x1815) */
static const ble_uuid16_t auto_io_svc_uuid = BLE_UUID16_INIT(0x1815);
static uint16_t led_chr_val_handle;
static const ble_uuid128_t led_chr_uuid =
    BLE_UUID128_INIT(0x23, 0xd1, 0xbc, 0xea, 0x5f, 0x78, 0x23, 0x15, 0xde, 0xef,
                     0x12, 0x12, 0x25, 0x15, 0x00, 0x00);

/* 3. Proprietary Configuration Service (node_id = 1022 = 0x03FE) */
/* E0C0DE00-0000-4000-8000-0000000003FE */
static const ble_uuid128_t config_svc_uuid =
    BLE_UUID128_INIT(0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                     0x00, 0x40, 0x00, 0x00, 0x00, 0xde, 0xc0, 0xe0);

/* E0C0DE01-0000-4000-8000-0000000003FE: Sampling Period (uint16) */
static uint16_t period_chr_val_handle;
static const ble_uuid128_t period_chr_uuid =
    BLE_UUID128_INIT(0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                     0x00, 0x40, 0x00, 0x00, 0x01, 0xde, 0xc0, 0xe0);

/* E0C0DE02-0000-4000-8000-0000000003FE: Access Code (text <= 32 bytes) */
static uint16_t passkey_chr_val_handle;
static const ble_uuid128_t passkey_chr_uuid =
    BLE_UUID128_INIT(0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                     0x00, 0x40, 0x00, 0x00, 0x02, 0xde, 0xc0, 0xe0);

/* GATT services table */
static const struct ble_gatt_svc_def gatt_svr_svcs[] = {
    /* Environmental Sensing Service */
    {.type = BLE_GATT_SVC_TYPE_PRIMARY,
     .uuid = &ess_svc_uuid.u,
     .characteristics =
         (struct ble_gatt_chr_def[]){
             {/* Temperature characteristic */
              .uuid = &temp_chr_uuid.u,
              .access_cb = temp_chr_access,
              .flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_NOTIFY,
              .val_handle = &temp_chr_val_handle},
             {/* Humidity characteristic */
              .uuid = &humidity_chr_uuid.u,
              .access_cb = humidity_chr_access,
              .flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_NOTIFY,
              .val_handle = &humidity_chr_val_handle},
             {0}}},

    /* Automation IO service */
    {.type = BLE_GATT_SVC_TYPE_PRIMARY,
     .uuid = &auto_io_svc_uuid.u,
     .characteristics =
         (struct ble_gatt_chr_def[]){
             {/* LED characteristic */
              .uuid = &led_chr_uuid.u,
              .access_cb = led_chr_access,
              .flags = BLE_GATT_CHR_F_WRITE,
              .val_handle = &led_chr_val_handle},
             {0}}},

    /* Proprietary Configuration service (Protected by SMP pairing/bonding) */
    {.type = BLE_GATT_SVC_TYPE_PRIMARY,
     .uuid = &config_svc_uuid.u,
     .characteristics =
         (struct ble_gatt_chr_def[]){
             {/* Sampling period characteristic */
              .uuid = &period_chr_uuid.u,
              .access_cb = period_chr_access,
              .flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_READ_ENC |
                       BLE_GATT_CHR_F_WRITE | BLE_GATT_CHR_F_WRITE_ENC |
                       BLE_GATT_CHR_F_WRITE_AUTHEN,
              .val_handle = &period_chr_val_handle},
             {/* Access code characteristic (write-only, authenticated) */
              .uuid = &passkey_chr_uuid.u,
              .access_cb = passkey_chr_access,
              .flags = BLE_GATT_CHR_F_WRITE | BLE_GATT_CHR_F_WRITE_ENC |
                       BLE_GATT_CHR_F_WRITE_AUTHEN,
              .val_handle = &passkey_chr_val_handle},
             {0}}},

    {0}, /* No more services. */
};

/* Private functions */
static int temp_chr_access(uint16_t conn_handle, uint16_t attr_handle,
                           struct ble_gatt_access_ctxt *ctxt, void *arg) {
    if (ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR) {
        int16_t temp = 0;
        uint16_t hum = 0;
        sensor_data_get(&temp, &hum);
        ESP_LOGI(TAG, "GATT Read Temperature: %d (0.01 C)", temp);
        int rc = os_mbuf_append(ctxt->om, &temp, sizeof(temp));
        return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
    }
    ESP_LOGE(TAG, "Unexpected op to temperature characteristic: %d", ctxt->op);
    return BLE_ATT_ERR_UNLIKELY;
}

static int humidity_chr_access(uint16_t conn_handle, uint16_t attr_handle,
                               struct ble_gatt_access_ctxt *ctxt, void *arg) {
    if (ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR) {
        int16_t temp = 0;
        uint16_t hum = 0;
        sensor_data_get(&temp, &hum);
        ESP_LOGI(TAG, "GATT Read Humidity: %u (0.01 %%)", hum);
        int rc = os_mbuf_append(ctxt->om, &hum, sizeof(hum));
        return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
    }
    ESP_LOGE(TAG, "Unexpected op to humidity characteristic: %d", ctxt->op);
    return BLE_ATT_ERR_UNLIKELY;
}

static int period_chr_access(uint16_t conn_handle, uint16_t attr_handle,
                             struct ble_gatt_access_ctxt *ctxt, void *arg) {
    if (ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR) {
        uint16_t period = get_sampling_period();
        ESP_LOGI(TAG, "GATT Read Sampling Period: %u s", period);
        int rc = os_mbuf_append(ctxt->om, &period, sizeof(period));
        return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
    } else if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {
        uint16_t len = OS_MBUF_PKTLEN(ctxt->om);
        if (len != 2) {
            ESP_LOGW(TAG, "Write period rejected: invalid length %u (expected 2)", len);
            return BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN;
        }
        uint16_t new_period = 0;
        int rc = ble_hs_mbuf_to_flat(ctxt->om, &new_period, 2, NULL);
        if (rc != 0) {
            ESP_LOGE(TAG, "Failed to copy period from mbuf: %d", rc);
            return BLE_ATT_ERR_UNLIKELY;
        }
        if (new_period < 1 || new_period > 3600) {
            ESP_LOGW(TAG, "Write period rejected: value %u out of range [1, 3600]", new_period);
            return BLE_ATT_ERR_VALUE_NOT_ALLOWED;
        }
        set_sampling_period(new_period);
        ESP_LOGI(TAG, "Sampling period updated to %u s", new_period);
        return 0;
    }
    ESP_LOGE(TAG, "Unexpected op to period characteristic: %d", ctxt->op);
    return BLE_ATT_ERR_UNLIKELY;
}

static int passkey_chr_access(uint16_t conn_handle, uint16_t attr_handle,
                              struct ble_gatt_access_ctxt *ctxt, void *arg) {
    if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {
        uint16_t len = OS_MBUF_PKTLEN(ctxt->om);
        if (len < 1 || len > 32) {
            ESP_LOGW(TAG, "Write access code rejected: invalid length %u (expected 1-32)", len);
            return BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN;
        }
        uint8_t buffer[32];
        int rc = ble_hs_mbuf_to_flat(ctxt->om, buffer, len, NULL);
        if (rc != 0) {
            return BLE_ATT_ERR_UNLIKELY;
        }
        /* Requirement: The value is NEVER printed to console; only its length is logged */
        ESP_LOGI(TAG, "Access code written successfully (length = %u bytes)", len);
        return 0;
    }
    ESP_LOGE(TAG, "Unexpected op to access code characteristic: %d", ctxt->op);
    return BLE_ATT_ERR_UNLIKELY;
}

static int led_chr_access(uint16_t conn_handle, uint16_t attr_handle,
                          struct ble_gatt_access_ctxt *ctxt, void *arg) {
    if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {
        if (ctxt->om->om_len == 1) {
            if (ctxt->om->om_data[0]) {
                led_on();
                ESP_LOGI(TAG, "led turned on!");
            } else {
                led_off();
                ESP_LOGI(TAG, "led turned off!");
            }
            return 0;
        }
        return BLE_ATT_ERR_UNLIKELY;
    }
    return BLE_ATT_ERR_UNLIKELY;
}

/* Public functions */
void gatt_svr_notify_sensor_data(void) {
    int16_t temp = 0;
    uint16_t hum = 0;
    sensor_data_get(&temp, &hum);
    ESP_LOGI(TAG, "Notifying subscribers: Temp=%d (0.01 C), Hum=%u (0.01 %%)", temp, hum);
    ble_gatts_chr_updated(temp_chr_val_handle);
    ble_gatts_chr_updated(humidity_chr_val_handle);
}

void gatt_svr_register_cb(struct ble_gatt_register_ctxt *ctxt, void *arg) {
    char buf[BLE_UUID_STR_LEN];
    switch (ctxt->op) {
    case BLE_GATT_REGISTER_OP_SVC:
        ESP_LOGI(TAG, "registered service %s with handle=%d",
                 ble_uuid_to_str(ctxt->svc.svc_def->uuid, buf),
                 ctxt->svc.handle);
        break;
    case BLE_GATT_REGISTER_OP_CHR:
        ESP_LOGI(TAG,
                 "registering characteristic %s with def_handle=%d val_handle=%d",
                 ble_uuid_to_str(ctxt->chr.chr_def->uuid, buf),
                 ctxt->chr.def_handle, ctxt->chr.val_handle);
        break;
    case BLE_GATT_REGISTER_OP_DSC:
        ESP_LOGI(TAG, "registering descriptor %s with handle=%d",
                 ble_uuid_to_str(ctxt->dsc.dsc_def->uuid, buf),
                 ctxt->dsc.handle);
        break;
    default:
        break;
    }
}

int gatt_svc_init(void) {
    int rc = 0;
    ble_svc_gatt_init();
    rc = ble_gatts_count_cfg(gatt_svr_svcs);
    if (rc != 0) {
        return rc;
    }
    rc = ble_gatts_add_svcs(gatt_svr_svcs);
    if (rc != 0) {
        return rc;
    }
    return 0;
}
