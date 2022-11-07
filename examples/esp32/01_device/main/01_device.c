/************************************************************************
 * 设置ticos_onloop函数触发间隔，若不设置，则默认为200毫秒
 ************************************************************************/
#define TICOS_HEARTBEAT_MILLIS 250

#include <ticos_framework.h>
#include <ticos/log.h>

/************************************************************************
 * 向工程注册总线标识号，请将此标识号列表成员作为TICOS_BUS首参
 ************************************************************************/
TICOS_BUS_ID_BEGIN
    // TODO 更多总线标识号
TICOS_BUS_ID_END

#include "ticos_hal.h"

/************************************************************************
 * 生命周期函数，按照一定时间间隔(TICOS_HEARTBEAT_MILLIS)触发
 ************************************************************************/
int ticos_onloop(void) {
    // 检查IO1设备缓存中的level值是否已被更新
    ticos_gpio_t* io_1 = ticos_dev(IO1);
    if (ticos_isdirty(io_1, level)) {
        bool level = ticos_get(io_1, level);
        // 当IO1电平变化时将DEV_IO3设置为反相
        ticos_dev_setval(IO3, level, !level);
    }
    return TICOS_OK;
}
