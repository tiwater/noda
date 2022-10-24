/*************************************************************************
* @file noda_iot
* @brief 设备接口头文件
* @author
* @date 2022-10-24 16:56:15
* @copyright
************************************************************************/

#ifndef __NODA_IOT_H
#define __NODA_IOT_H

#include "noda/device.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************
  * noda_iot类定义
  ************************************************************************/
NODA_DEV_CLASS_BEGIN(noda_iot);
    const char* ssid;
    const char* pswd;
    NODA_VAR(bool, prop_switch);
    NODA_VAR(bool, prop_led);
NODA_DEV_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __NODA_IOT_H
