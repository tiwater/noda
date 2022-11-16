#ifndef __TICOS_CONFIG_H
#define __TICOS_CONFIG_H

#include <ticos/bus_center.h>
#include <ticos/device_center.h>

#include <ticos/device/gpio.h>
#include "ticos_iot.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 * 向工程注册总线
 ************************************************************************/
TICOS_BUS_BEGIN
    // TODO 注册更多总线
TICOS_BUS_END

/************************************************************************
 * 向工程注册设备
 ************************************************************************/
TICOS_DEV_BEGIN
    TICOS_DEV(DEV_IOT, ticos_iot,
            /* 请填充测试所需的 WiFi ssid */
            .ssid = "SSID",
            /* 请填充测试所需的 WiFi password */
            .pswd = "PASSWORD",
            /* 请填充测试所需的 mqtt fqdn */
            .fqdn = "//hub.ticos.cn",
            /* 请填充测试所需的 product id */
            .product_id = "PRODUCT ID",
            /* 请填充测试所需的 device id */
            .device_id  = "DEVICE ID",
            /* 请填充测试所需的 security key */
            .secret_key = "SECRET KEY")
    TICOS_DEV(DEV_IO1, ticos_gpio, .pin=1, .mode=TICOS_GPIO_MODE_INPUT)
    TICOS_DEV(DEV_IO3, ticos_gpio, .pin=3, .mode=TICOS_GPIO_MODE_OUTPUT)
    // TODO 注册更多设备
TICOS_DEV_END

#ifdef __cplusplus
}
#endif

#endif // __TICOS_CONFIG_H
