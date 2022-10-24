/*************************************************************************
  * 设置noda_onloop函数触发间隔，若不配置，则默认为200毫秒
  ************************************************************************/
#define NODA_HEARTBEAT_MILLIS 1000

#include <noda.h>
#include <noda/log.h>
#include <noda/bus/i2c.h>

#include "silan_sc7a20.h"

/*************************************************************************
  * 向工程注册总线标识号，请将此标识号列表成员作为NODA_BUS_ADD首参
  ************************************************************************/
NODA_BUS_ID_BEGIN
    I2C0,
    // TODO 更多总线标识号
NODA_BUS_ID_END

/*************************************************************************
  * 向工程注册设备标识号，请将此标识号列表成员作为NODA_DEVICE_ADD首参
  ************************************************************************/
NODA_DEV_ID_BEGIN
    GSENSOR,
    // TODO 更多设备标识号
NODA_DEV_ID_END

/*************************************************************************
  * 生命周期函数，负责系统启动后的自定义初始化工作
  ************************************************************************/
int noda_onboot(void) {
    NODA_BUS_ADD(I2C0, noda_i2c, .port=0, .sda=7, .scl=6, .freq=100);
    NODA_DEV_ADD(GSENSOR, silan_sc7a20, .bus=I2C0, .addr=0x19, .rw_wait_ms=1000);
    return NODA_OK;
}

/*************************************************************************
  * 生命周期函数，按照一定时间间隔(NODA_HEARTBEAT_MILLIS)触发
  ************************************************************************/
int noda_onloop(void) {
    // 输出从GSENSOR设备缓存中得到的三轴数据
    silan_sc7a20_t* gs = noda_dev(GSENSOR, silan_sc7a20);
    float x = noda_get(gs, x);
    float y = noda_get(gs, y);
    float z = noda_get(gs, z);
    noda_logd("%s x = %f, y = %f, z = %f", noda_dev_name(GSENSOR), x, y, z);
    return NODA_OK;
}
