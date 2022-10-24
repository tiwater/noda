/*************************************************************************
* @file silan_sc7a20
* @brief 设备接口头文件
* @author
* @date 2022-10-24 16:56:15
* @copyright
************************************************************************/

#ifndef __SILAN_SC7A20_H
#define __SILAN_SC7A20_H

#include "noda/device.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************
  * silan_sc7a20类定义
  ************************************************************************/
NODA_DEV_CLASS_BEGIN(silan_sc7a20);
    uint8_t     bus;
    uint8_t     addr;
    uint16_t    rw_wait_ms;
    NODA_VAR(float, x);
    NODA_VAR(float, y);
    NODA_VAR(float, z);
NODA_DEV_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __SILAN_SC7A20_H
