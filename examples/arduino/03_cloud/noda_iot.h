/*************************************************************************
  * @class noda_iot 头文件
  * @generate date: 2022-10-22 23:53:41
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
NODA_DEVICE_CLASS_BEGIN(noda_iot);
    const char* ssid;
    const char* pswd;
    NODA_VAR(bool, prop_switch);
    NODA_VAR(bool, prop_led);
NODA_DEVICE_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __NODA_IOT_H
