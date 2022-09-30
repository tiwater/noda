#ifndef __HI_SENSOR_H
#define __HI_SENSOR_H

#include "noda_device.h"

#ifdef __cplusplus
extern "C" {
#endif

NODA_DEVICE_CLASS_BEGIN(hi_sensor);
    uint8_t     sda;
    uint8_t     scl;
    uint8_t     addr;
    uint16_t    freq;
    NODA_VAR(float, x);
    NODA_VAR(float, y);
    NODA_VAR(float, z);
NODA_DEVICE_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __HI_SENSOR_H
