#ifndef __TICOS_CONFIG_H
#define __TICOS_CONFIG_H

#include <ticos/bus_center.h>
#include <ticos/device_center.h>

#include <ticos/device/gpio.h>

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 * 向工程注册设备
 ************************************************************************/
TICOS_DEV_BEGIN
    TICOS_DEV(IO1, ticos_gpio, .pin=1, .mode=TICOS_GPIO_MODE_INPUT)
    TICOS_DEV(IO3, ticos_gpio, .pin=3, .mode=TICOS_GPIO_MODE_OUTPUT)
    // TODO 注册更多设备
TICOS_DEV_END

#ifdef __cplusplus
}
#endif

#endif // __TICOS_CONFIG_H
