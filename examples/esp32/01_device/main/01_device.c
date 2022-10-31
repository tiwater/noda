/************************************************************************
 * 设置ticos_onloop函数触发间隔，若不设置，则默认为200毫秒
 ************************************************************************/
#define TICOS_HEARTBEAT_MILLIS 250

#include <ticos.h>
#include <ticos/log.h>

#include <ticos/device/gpio.h>

/************************************************************************
 * 向工程注册总线标识号，请将此标识号列表成员作为TICOS_BUS_ADD首参
 ************************************************************************/
TICOS_BUS_ID_BEGIN
    // TODO 更多总线标识号
TICOS_BUS_ID_END

/************************************************************************
 * 向工程注册设备标识号，请将此标识号列表成员作为TICOS_DEV_ADD首参
 ************************************************************************/
TICOS_DEV_ID_BEGIN
    DEV_IO1,
    DEV_IO3,
    // TODO 更多设备标识号
TICOS_DEV_ID_END

/************************************************************************
 * 生命周期函数，负责系统启动后的自定义初始化工作
 ************************************************************************/
int ticos_onboot(void) {
    TICOS_DEV_ADD(DEV_IO1, ticos_gpio, .pin=1, .mode=TICOS_GPIO_MODE_INPUT);
    TICOS_DEV_ADD(DEV_IO3, ticos_gpio, .pin=3, .mode=TICOS_GPIO_MODE_OUTPUT);
    return TICOS_OK;
}

/************************************************************************
 * 生命周期函数，按照一定时间间隔(TICOS_HEARTBEAT_MILLIS)触发
 ************************************************************************/
int ticos_onloop(void) {
    // 检查DEV_IO1设备缓存中的level值是否已被更新
    ticos_gpio_t* io_1 = ticos_dev(DEV_IO1, ticos_gpio);
    if (ticos_isdirty(io_1, level)) {
        bool level = ticos_get(io_1, level);
        // 当DEV_IO1电平变化时将DEV_IO3设置为反相
        ticos_dev_setval(DEV_IO3, ticos_gpio, level, !level);
    }
    return TICOS_OK;
}
