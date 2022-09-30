#ifndef __HI_SENSOR_H
#define __HI_SENSOR_H

#include "noda_device.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************
  * 定义hi_sensor类
  ************************************************************************/
NODA_DEVICE_CLASS_BEGIN(hi_sensor);
    uint8_t     sda;    // 定义一般类成员变量
    uint8_t     scl;    // 一般成员变量不会被应用层感知，也无法操作
    uint8_t     addr;   // 如果希望成员变量被暴露，请使用NODA_VAR方式定义变量
    uint16_t    freq;
    NODA_VAR(float, x); // 通过NODA_VAR定义需要暴露的类成员变量
    NODA_VAR(float, y); // 定义后可以通过noda_getval/noda_setval读写数据
    NODA_VAR(float, z); // 支持任意数据类型
NODA_DEVICE_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __HI_SENSOR_H
