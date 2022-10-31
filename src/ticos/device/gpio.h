/*************************************************************************
  * @file ticos_gpio
  * @brief 设备接口头文件
  * @author
  * @date 2022-10-24 16:56:15
  * @copyright
  ************************************************************************/

#ifndef __TICOS_GPIO_H
#define __TICOS_GPIO_H

#include "ticos/device.h"

#ifdef __cplusplus
extern "C" {
#endif

enum ticos_gpio_mode_t {
    TICOS_GPIO_MODE_DISABLE,
    TICOS_GPIO_MODE_INPUT,
    TICOS_GPIO_MODE_OUTPUT,
};

/*************************************************************************
  * ticos_gpio类定义
  ************************************************************************/
TICOS_DEV_CLASS_BEGIN(ticos_gpio);
    ticos_pin_t pin;
    enum ticos_gpio_mode_t mode;
    TICOS_VAR(bool, level);
TICOS_DEV_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __TICOS_GPIO_H
