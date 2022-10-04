/*************************************************************************
  * 设置noda_onloop函数触发间隔，若不配置，则默认为200毫秒
  ************************************************************************/
#define NODA_HEARTBEAT_MILLIS 1000

#include <noda.h>
#include <noda_log.h>
#include <bus/noda_i2c.h>
#include <device/noda_ntc_sensor.h>

#include "hi_sensor.h"

NODA_BUS_ID_MAP {
    I2C0,
    I2C1,
    // TODO 更多总线标识号
    NODA_NBUS, /* 此行负责告知系统总线总数，请勿用于NODA_BUS_ADD首参 */
};

NODA_BUS_LIST {
    NODA_BUS_ADD(I2C0, noda_i2c, .sda=7, .scl=6),
    NODA_BUS_ADD(I2C1, noda_i2c, .sda=11, .scl=12),
    // TODO 更多总线注册
};

/*************************************************************************
  * 向工程注册设备标识号，系统将按此标识号列表的顺序对设备进行自动排序
  * 请将此标识号列表成员作为NODA_DEVICE_ADD首参
  * 开发者可据此标识号使用noda_isdirty/noda_getval/noda_setval读写设备数据
  ************************************************************************/
NODA_DEVICE_ID_MAP {
    NTC,
    HI,
    // TODO 更多设备标识号
    NODA_NDEV,  /* 此行负责告知系统设备总数，请勿用于NODA_DEVICE_ADD首参 */
};

/*************************************************************************
  * 向工程注册需要用到的设备
  * NODA_DEVICE_ADD首参为标识号，为设备唯一标识
  ************************************************************************/
NODA_DEVICE_LIST {
    NODA_DEVICE_ADD(NTC, noda_ntc_sensor, .pin=3, .chn=3, .vref=3300),
    NODA_DEVICE_ADD(HI, hi_sensor, .sda=7, .scl=6, .addr=5, .freq=100),
    // TODO 更多设备注册
};

/*************************************************************************
  * 生命周期函数，在系统启动后被尽快调用
  * 可以在此执行用户自定义的初始化操作
  ************************************************************************/
int noda_onstart(void) {
    noda_logd("noda_onstart");
    return NODA_OK;
}

/*************************************************************************
  * 生命周期函数，在系统结束运行前被最后调用
  * 可以在此执行用户自定义的清理操作
  ************************************************************************/
int noda_onclean(void) {
    noda_logd("noda_onclean");
    return NODA_OK;
}

/*************************************************************************
  * 生命周期函数，用于系统进入正式运行状态后按照一定时间间隔触发
  * 自定义触发间隔的方式：定义NODA_HEARTBEAT_MILLIS宏
  ************************************************************************/
int noda_onloop(void) {
    static int counter = 0;
    noda_logd("noda_loop %d", counter++);
    // 输出从ntc设备缓存中得到的最新adc值
    int adc = noda_getval(NTC, noda_ntc_sensor, adc);
    noda_logd("noda_ntc_sensor adc = %d", adc);

    // 输出从hi设备缓存中得到的三轴数据
    float x = noda_getval(HI, hi_sensor, x);
    float y = noda_getval(HI, hi_sensor, y);
    float z = noda_getval(HI, hi_sensor, z);
    noda_logd("hi_sensor x = %f, y = %f, z = %f", x, y, z);
    return counter > 10 ? NODA_FAIL : NODA_OK;
}
