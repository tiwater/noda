/*************************************************************************
  * 设置noda_onloop函数触发间隔，若不设置，则默认为200毫秒
  ************************************************************************/
#define NODA_HEARTBEAT_MILLIS 250
#include <noda.h>
#include <noda/log.h>
#include <noda/device/gpio.h>
#include "noda_iot.h"

/* 请填充测试所需的 WiFi ssid */
#define _SSID ""
/* 请填充测试所需的 WiFi password */
#define _PSWD ""

/*************************************************************************
  * 系统默认使用总线(BUS)管理协议复用，若项目不需要启用，请使用此声明
  ************************************************************************/
NODA_NO_BUS;

/*************************************************************************
  * 向工程注册设备标识号，系统将按此标识号列表的顺序对设备进行自动排序
  * 请将此标识号列表成员作为NODA_DEVICE_ADD首参
  * 开发者可据此标识号使用noda_isdirty/noda_getval/noda_setval读写设备数据
  ************************************************************************/
NODA_DEVICE_ID_MAP {
    DEV_IOT,
    DEV_IO1,
    DEV_IO3,
    // TODO 更多设备标识号
    NODA_NDEV,  /* 此行负责告知系统设备总数，请勿用于NODA_DEVICE_ADD首参 */
};

/*************************************************************************
  * 向工程注册需要用到的设备
  * NODA_DEVICE_ADD首参为标识号，为设备唯一标识
  ************************************************************************/
NODA_DEVICE_LIST {
    NODA_DEVICE_ADD(DEV_IOT, noda_iot, .ssid=_SSID, .pswd=_PSWD);
    NODA_DEVICE_ADD(DEV_IO1, noda_gpio, .pin=16, .mode=NODA_GPIO_MODE_INPUT);
    NODA_DEVICE_ADD(DEV_IO3, noda_gpio, .pin=7, .mode=NODA_GPIO_MODE_OUTPUT);
    // TODO 更多设备注册
}

/*************************************************************************
  * 生命周期函数，可以在此执行用户自定义的初始化操作
  ************************************************************************/
int noda_onstart() {
    noda_logd("noda_onstart");
    return NODA_OK;
}

/*************************************************************************
  * 生命周期函数，可以在此执行用户自定义的清理操作
  ************************************************************************/
int noda_onclean(void) {
    noda_logd("noda_onclean");
    return NODA_OK;
}

static bool g_light_on;

static void set_light(bool on) {
    noda_iot_t* iot = noda_dev(DEV_IOT, noda_iot);
    noda_set(iot, prop_switch, on);
    noda_set(iot, prop_led, on);

    noda_dev_setval(DEV_IO3, noda_gpio, level, on);

    g_light_on = on;
}

static inline void switch_light(void) {
    set_light(!g_light_on);
}

/*************************************************************************
  * 生命周期函数，按照一定时间间隔(NODA_HEARTBEAT_MILLIS)触发
  ************************************************************************/
int noda_onloop() {
    
    noda_iot_t* iot = noda_dev(DEV_IOT, noda_iot);
    if (noda_isdirty(iot, prop_switch)) {
        bool on = noda_get(iot, prop_switch);
        set_light(on);
    }

    noda_gpio_t* io_1 = noda_dev(DEV_IO1, noda_gpio);
    if (noda_isdirty(io_1, level)) {
        if (!noda_get(io_1, level)) {
            switch_light();
        }
    }

    return NODA_OK;
}
