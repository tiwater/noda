/************************************************************************
 * 设置ticos_onloop函数触发间隔，若不设置，则默认为200毫秒
 ************************************************************************/
#define NODA_HEARTBEAT_MILLIS 250

#include <noda.h>
#include <noda/log.h>
#include <noda/device/gpio.h>
#include "ticos_iot.h"

/* 请填充测试所需的 WiFi ssid */
#define _SSID ""
/* 请填充测试所需的 WiFi password */
#define _PSWD ""
/* 请填充测试所需的 mqtt fqdn */
#define _FQDN "mqtt://hub.ticos.cn"
/* 请填充测试所需的 product id */
#define _PRD_ID "HITXM3K4IE"
/* 请填充测试所需的 device id */
#define _DEV_ID "SLC1"
/* 请填充测试所需的 security key */
#define _SKEY   "SKEY"

/************************************************************************
 * 向工程注册总线标识号，请将此标识号列表成员作为NODA_BUS_ADD首参
 ************************************************************************/
NODA_BUS_ID_BEGIN
    // TODO 更多总线标识号
NODA_BUS_ID_END

/************************************************************************
 * 向工程注册设备标识号，请将此标识号列表成员作为NODA_DEV_ADD首参
 ************************************************************************/
NODA_DEV_ID_BEGIN
    DEV_IOT,
    DEV_IO1,
    DEV_IO3,
    // TODO 更多设备标识号
NODA_DEV_ID_END

/************************************************************************
 * 生命周期函数，负责系统启动后的自定义初始化工作
 ************************************************************************/
int ticos_onboot(void) {
    NODA_DEV_ADD(DEV_IOT, ticos_iot, .ssid=_SSID, .pswd=_PSWD, .fqdn=_FQDN, .pid=_PRD_ID, .did=_DEV_ID, .skey=_SKEY);
    NODA_DEV_ADD(DEV_IO1, ticos_gpio, .pin=16, .mode=NODA_GPIO_MODE_INPUT);
    NODA_DEV_ADD(DEV_IO3, ticos_gpio, .pin=7, .mode=NODA_GPIO_MODE_OUTPUT);
    return NODA_OK;
}

static bool g_light_on;

static void set_light(bool on) {
    ticos_iot_t* iot = ticos_dev(DEV_IOT, ticos_iot);
    // 设置属性值
    ticos_set(iot, prop_switch, on);
    ticos_set(iot, prop_led, on);

    ticos_dev_setval(DEV_IO3, ticos_gpio, level, on);

    g_light_on = on;
}

static inline void switch_light(void) {
    set_light(!g_light_on);
}

/************************************************************************
 * 生命周期函数，按照一定时间间隔(NODA_HEARTBEAT_MILLIS)触发
 ************************************************************************/
int ticos_onloop(void) {
    
    ticos_iot_t* iot = ticos_dev(DEV_IOT, ticos_iot);
    if (ticos_isdirty(iot, prop_switch)) {
        bool on = ticos_get(iot, prop_switch);
        set_light(on);
    }

    ticos_gpio_t* io_1 = ticos_dev(DEV_IO1, ticos_gpio);
    if (ticos_isdirty(io_1, level)) {
        if (!ticos_get(io_1, level)) {
            switch_light();
        }
    }

    return NODA_OK;
}
