#ifndef __TICOS_CONFIG_H
#define __TICOS_CONFIG_H

#include <ticos/bus_center.h>
#include <ticos/device_center.h>

#include <ticos/bus/i2c.h>
#include "silan_sc7a20.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 * 向工程注册总线
 ************************************************************************/
TICOS_BUS_BEGIN
    TICOS_BUS(I2C0, ticos_i2c, .port=0, .sda=7, .scl=6, .freq=100)
    // TODO 注册更多总线
TICOS_BUS_END


/************************************************************************
 * 向工程注册设备
 ************************************************************************/
TICOS_DEV_BEGIN
    TICOS_DEV(GSENSOR, silan_sc7a20, .bus=(ticos_bus_t*)I2C0, .addr=0x19, .rw_wait_ms=1000)
    // TODO 注册更多设备
TICOS_DEV_END

#ifdef __cplusplus
}
#endif

#endif // __TICOS_CONFIG_H
