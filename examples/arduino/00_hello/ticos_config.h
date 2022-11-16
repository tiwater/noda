#ifndef __TICOS_CONFIG_H
#define __TICOS_CONFIG_H

#include <ticos/bus_center.h>
#include <ticos/device_center.h>

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 * 向工程注册总线
 ************************************************************************/
TICOS_BUS_BEGIN
    // TODO 注册更多总线
TICOS_BUS_END

/************************************************************************
 * 向工程注册设备
 ************************************************************************/
TICOS_DEV_BEGIN
    // TODO 注册更多设备
TICOS_DEV_END

#ifdef __cplusplus
}
#endif

#endif // __TICOS_CONFIG_H
