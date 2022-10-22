/*************************************************************************
  * @class noda_gpio 头文件
  * @generate date: 2022-10-06 21:11:46
  ************************************************************************/

#ifndef __NODA_GPIO_H
#define __NODA_GPIO_H

#include "noda/device.h"

#ifdef __cplusplus
extern "C" {
#endif

enum noda_gpio_mode_t {
    NODA_GPIO_MODE_DISABLE,
    NODA_GPIO_MODE_INPUT,
    NODA_GPIO_MODE_OUTPUT,
};

/*************************************************************************
  * noda_gpio类定义
  ************************************************************************/
NODA_DEVICE_CLASS_BEGIN(noda_gpio);
    noda_pin_t pin;
    enum noda_gpio_mode_t mode;
    NODA_VAR(bool, level);
NODA_DEVICE_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __NODA_GPIO_H
