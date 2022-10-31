/************************************************************************
 * @file ticos_iot
 * @brief 设备接口头文件
 * @author
 * @date 2022-10-28 23:58:46
 * @copyright
 ************************************************************************/

#ifndef __TICOS_IOT_H
#define __TICOS_IOT_H

#include "ticos/device.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 * ticos_iot类定义
 ************************************************************************/
TICOS_DEV_CLASS_BEGIN(ticos_iot);
    const char* ssid;
    const char* pswd;
    const char* fqdn;
    const char* pid;
    const char* did;
    const char* skey;
    TICOS_VAR(bool, prop_switch);
    TICOS_VAR(bool, prop_led);
TICOS_DEV_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __TICOS_IOT_H
