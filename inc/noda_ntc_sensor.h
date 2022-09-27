#ifndef __NODA_NTC_SENSOR_H
#define __NODA_NTC_SENSOR_H

#include "noda_device.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct noda_ntc_sensor_t {
    NODA_DEVICE_BASE(noda_ntc_sensor_t);
    uint8_t     pin;
    uint8_t     chn;
    uint16_t    vref;
} noda_ntc_sensor_t;

int noda_ntc_sensor_open(noda_ntc_sensor_t* self);

int noda_ntc_sensor_close(noda_ntc_sensor_t* self);

int noda_ntc_sensor_power_mode_changed(noda_ntc_sensor_t* self, noda_power_mode_t mode);

int noda_ntc_sensor_read(noda_ntc_sensor_t* self, int c, uint8_t* data);

int noda_ntc_sensor_write(noda_ntc_sensor_t* self, int c, const uint8_t* data);

#ifdef __cplusplus
}
#endif

#endif // __NODA_NTC_SENSOR_H
