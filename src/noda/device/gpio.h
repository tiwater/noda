/*************************************************************************
  * @file noda_gpio
  * @brief 设备接口头文件
  * @author
  * @date 2022-10-24 16:56:15
  * @copyright
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
NODA_DEV_CLASS_BEGIN(noda_gpio);
    noda_pin_t pin;
    enum noda_gpio_mode_t mode;
    NODA_VAR(bool, level);
NODA_DEV_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __NODA_GPIO_H
