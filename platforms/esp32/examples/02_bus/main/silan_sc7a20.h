/*************************************************************************
  * @class silan_sc7a20 头文件
  * @generate date: 2022-10-08 10:07:30
  ************************************************************************/

#ifndef __SILAN_SC7A20_H
#define __SILAN_SC7A20_H

#include "noda_device.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************
  * silan_sc7a20类定义
  ************************************************************************/
NODA_DEVICE_CLASS_BEGIN(silan_sc7a20);
    uint8_t     bus;
    uint8_t     addr;
    uint16_t    rw_wait_ms;
    NODA_VAR(float, x);
    NODA_VAR(float, y);
    NODA_VAR(float, z);
NODA_DEVICE_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __SILAN_SC7A20_H
