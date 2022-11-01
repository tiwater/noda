/************************************************************************
 * @file noda_iot
 * @brief 设备接口头文件
 * @author
 * @date 2022-11-01 09:06:27
 * @copyright
 ************************************************************************/

#ifndef __NODA_IOT_H
#define __NODA_IOT_H

#include "noda/device.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 * noda_iot类定义
 ************************************************************************/
NODA_DEV_CLASS_BEGIN(noda_iot);
    const char* ssid;
    const char* pswd;
    const char* fqdn;
    const char* product_id;
    const char* device_id;
    const char* secret_key;
    NODA_VAR(bool, prop_switch);
    NODA_VAR(bool, prop_led);
NODA_DEV_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __NODA_IOT_H
