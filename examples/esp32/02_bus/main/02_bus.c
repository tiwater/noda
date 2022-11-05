/************************************************************************
 * 设置ticos_onloop函数触发间隔，若不配置，则默认为200毫秒
 ************************************************************************/
#define TICOS_HEARTBEAT_MILLIS 1000

#include <ticos_framework.h>
#include <ticos/log.h>
#include <ticos/bus/i2c.h>

#include "silan_sc7a20.h"

/************************************************************************
 * 向工程注册总线标识号，请将此标识号列表成员作为TICOS_BUS首参
 ************************************************************************/
TICOS_BUS_ID_BEGIN
    I2C0,
    // TODO 更多总线标识号
TICOS_BUS_ID_END

/************************************************************************
 * 向工程注册设备标识号，请将此标识号列表成员作为TICOS_DEV首参
 ************************************************************************/
TICOS_DEV_ID_BEGIN
    GSENSOR,
    // TODO 更多设备标识号
TICOS_DEV_ID_END

/************************************************************************
 * 生命周期函数，负责系统启动后的自定义初始化工作
 ************************************************************************/
int ticos_onboot(void) {
    TICOS_BUS(I2C0, ticos_i2c, .port=0, .sda=7, .scl=6, .freq=100);
    TICOS_DEV(GSENSOR, silan_sc7a20, .bus=I2C0, .addr=0x19, .rw_wait_ms=1000);
    return TICOS_OK;
}

/************************************************************************
 * 生命周期函数，按照一定时间间隔(TICOS_HEARTBEAT_MILLIS)触发
 ************************************************************************/
int ticos_onloop(void) {
    // 输出从GSENSOR设备缓存中得到的三轴数据
    silan_sc7a20_t* gs = ticos_dev(GSENSOR, silan_sc7a20);
    float x = ticos_get(gs, x);
    float y = ticos_get(gs, y);
    float z = ticos_get(gs, z);
    ticos_logd("%s x = %f, y = %f, z = %f", ticos_dev_name(GSENSOR), x, y, z);
    return TICOS_OK;
}
