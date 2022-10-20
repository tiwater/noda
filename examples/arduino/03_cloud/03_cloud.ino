/*************************************************************************
  * 设置noda_onloop函数触发间隔，若不设置，则默认为200毫秒
  ************************************************************************/
#define NODA_HEARTBEAT_MILLIS 250
#include <noda.h>
#include <noda/log.h>
#include <noda/device/gpio.h>
#include "noda_iot.h"

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
    NODA_DEVICE_ADD(DEV_IOT, noda_iot, .pid=0, .did=0, .skey=0);
    NODA_DEVICE_ADD(DEV_IO1, noda_gpio, .pin=1, .mode=NODA_GPIO_MODE_INPUT);
    NODA_DEVICE_ADD(DEV_IO3, noda_gpio, .pin=3, .mode=NODA_GPIO_MODE_OUTPUT);
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

/*************************************************************************
  * 生命周期函数，按照一定时间间隔(NODA_HEARTBEAT_MILLIS)触发
  ************************************************************************/
int noda_onloop() {
    // 检查DEV_IO1设备缓存中的level值是否已被更新
    noda_gpio_t* io_1 = noda_dev(DEV_IO1, noda_gpio);
    if (noda_isdirty(io_1, level)) {
        bool level = noda_get(io_1, level);
        // 当DEV_IO1电平变化时将DEV_IO3设置为反相
        noda_dev_setval(DEV_IO3, noda_gpio, level, !level);
        noda_dev_setval(DEV_IOT, noda_iot, prop_switch, level);
    }
    return NODA_OK;
}
