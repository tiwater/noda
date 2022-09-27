#ifndef __NODA_NTC_SENSOR_H
#define __NODA_NTC_SENSOR_H

#include "noda_device.h"

#ifdef __cplusplus
extern "C" {
#endif

NODA_DEVICE_CLASS_BEGIN(noda_ntc_sensor);
    uint8_t     pin;
    uint8_t     chn;
    uint16_t    vref;
NODA_DEVICE_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __NODA_NTC_SENSOR_H
