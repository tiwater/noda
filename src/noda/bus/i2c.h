#ifndef __NODA_I2C_H
#define __NODA_I2C_H

#include "noda/bus.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************
  * ticos_i2c类定义
  ************************************************************************/
NODA_BUS_CLASS_BEGIN(ticos_i2c);
    const uint8_t       port;
    const ticos_pin_t    sda;
    const ticos_pin_t    scl;
    uint16_t            freq;
NODA_BUS_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __NODA_I2C_H
