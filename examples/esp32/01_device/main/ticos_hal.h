#ifndef __TICOS_HAL_H
#define __TICOS_HAL_H

#include <ticos/device_center.h>

#include <ticos/device/gpio.h>

#ifdef __cplusplus
extern "C" {
}
#endif

/************************************************************************
 * 向工程注册设备标识号，请将此标识号列表成员作为TICOS_DEV首参
 ************************************************************************/
TICOS_DEV_ID_BEGIN
    TICOS_DEV_ID(IO1, ticos_gpio);
    TICOS_DEV_ID(IO3, ticos_gpio);
    // TODO 更多设备标识号
TICOS_DEV_ID_END

#ifdef TICOS_HEARTBEAT_MILLIS

/************************************************************************
 * 生命周期函数，负责系统启动后的自定义初始化工作
 ************************************************************************/
int ticos_onboot(void) {
    TICOS_DEV(IO1, ticos_gpio, .pin=1, .mode=TICOS_GPIO_MODE_INPUT);
    TICOS_DEV(IO3, ticos_gpio, .pin=3, .mode=TICOS_GPIO_MODE_OUTPUT);
    return TICOS_OK;
}

#endif

#ifdef __cplusplus
}
#endif

#endif // __TICOS_HAL_H
