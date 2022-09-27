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
    bool        opened;
} noda_ntc_sensor_t;

#define noda_ntc_sensor(...)  \
    (noda_ntc_sensor_t) { __VA_ARGS__ }

#ifdef __cplusplus
}
#endif

#endif // __NODA_NTC_SENSOR_H
