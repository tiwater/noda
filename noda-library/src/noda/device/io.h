/*************************************************************************
  * @class noda_io 头文件
  * @generate date: 2022-10-06 21:11:46
  ************************************************************************/

#ifndef __NODA_IO_H
#define __NODA_IO_H

#include "noda/device.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************
  * noda_io类定义
  ************************************************************************/
NODA_DEVICE_CLASS_BEGIN(noda_io);
    noda_pin_t pin;
    NODA_VAR(bool, level);
NODA_DEVICE_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __NODA_IO_H
