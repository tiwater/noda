/*************************************************************************
  * 设置noda_onloop函数触发间隔，若不配置，则默认为200毫秒
  ************************************************************************/
#define NODA_HEARTBEAT_MILLIS 1000

#include <noda.h>
#include <noda_device_center.h>
#include <device/noda_ntc_sensor.h>
#include <noda_log.h>

#include "hi_sensor.h"

/*************************************************************************
  * 向工程注册需要用到的设备
  * name为必填项，为设备唯一标识，后期通过name字符串获取设备句柄
  ************************************************************************/
NODA_DEVICE_LIST {
    NODA_DEVICE_ADD(noda_ntc_sensor, .name="ntc", .pin=3, .chn=3, .vref=3300)
    NODA_DEVICE_ADD(hi_sensor, .name="hi", .sda=7, .scl=6, .addr=5, .freq=100)
//    NODA_DEVICE_ADD(silan_sc7a20, .name="accel", .sda=7, .scl=6, .addr=25, .freq=100)
//    NODA_DEVICE_ADD(hx711, .name="weigh", .pwr=5, .sck=20, .dout=21, .gain=1)
//    NODA_DEVICE_ADD(ws2812rmt, .name="led", .pin=10, .chn=0, .nums=6)
};

/*************************************************************************
  * 生命周期函数，在系统启动后被尽快调用
  ************************************************************************/
int noda_startup(int argc, const char** argv) {
    for (int i = 0; i < argc; ++i) {
        noda_print("%s ", argv[i]);
    }
    noda_print("\n");
    noda_device_center_startup();
    return NODA_OK;
}

/*************************************************************************
  * 生命周期函数，在系统结束运行前被最后调用
  ************************************************************************/
int noda_cleanup(void) {
    noda_device_center_cleanup();
    noda_logd("noda_cleanup");
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
    int adc = noda_getval(noda_ntc_sensor, "ntc", adc);
    noda_logd("noda_ntc_sensor adc = %d", adc);

    // 输出从hi设备缓存中得到的三轴数据
    float x = noda_getval(hi_sensor, "hi", x);
    float y = noda_getval(hi_sensor, "hi", y);
    float z = noda_getval(hi_sensor, "hi", z);
    noda_logd("hi_sensor x = %f, y = %f, z = %f", x, y, z);
    return counter > 10 ? NODA_FAIL : NODA_OK;
}
