#ifndef __NODA_I2C_H
#define __NODA_I2C_H

#include "noda_bus.h"

#ifdef __cplusplus
extern "C" {
#endif

NODA_BUS_CLASS_BEGIN(noda_i2c);
    uint8_t     sda;
    uint8_t     scl;
NODA_BUS_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __NODA_I2C_H
