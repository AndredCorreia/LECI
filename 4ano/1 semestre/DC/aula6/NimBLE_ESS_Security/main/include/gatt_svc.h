#ifndef GATT_SVR_H
#define GATT_SVR_H

/* Includes */
#include "host/ble_gatt.h"
#include "services/gatt/ble_svc_gatt.h"
#include "host/ble_gap.h"

/* Public function declarations */
void gatt_svr_notify_sensor_data(void);
void gatt_svr_register_cb(struct ble_gatt_register_ctxt *ctxt, void *arg);
int gatt_svc_init(void);

#endif // GATT_SVR_H
