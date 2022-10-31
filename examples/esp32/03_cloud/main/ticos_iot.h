/************************************************************************
 * @file ticos_iot
 * @brief 设备接口头文件
 * @author
 * @date 2022-10-28 23:58:46
 * @copyright
 ************************************************************************/

#ifndef __NODA_IOT_H
#define __NODA_IOT_H

#include "noda/device.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 * ticos_iot类定义
 ************************************************************************/
NODA_DEV_CLASS_BEGIN(ticos_iot);
    const char* ssid;
    const char* pswd;
    const char* fqdn;
    const char* pid;
    const char* did;
    const char* skey;
    NODA_VAR(bool, prop_switch);
    NODA_VAR(bool, prop_led);
NODA_DEV_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __NODA_IOT_H
