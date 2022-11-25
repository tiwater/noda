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

/*************************************************************************
  * ticos_gpio_mode，可选的 GPIO 引脚模式
  ************************************************************************/
enum ticos_gpio_mode_t {
    TICOS_GPIO_MODE_DISABLE,    /**< GPIO 模式，将引脚配置为无效 */
    TICOS_GPIO_MODE_INPUT,      /**< GPIO 模式，将引脚配置为输入 */
    TICOS_GPIO_MODE_OUTPUT,     /**< GPIO 模式，将引脚配置为输出 */
};

/*************************************************************************
  * ticos_gpio 类，用于将引脚配置为 GPIO
  ************************************************************************/
TICOS_DEV_CLASS_BEGIN(ticos_gpio);
    ticos_pin_t pin;                /**< GPIO 引脚号 */
    enum ticos_gpio_mode_t mode;    /**< GPIO 引脚模式，可选 TICOS_GPIO_MODE_DISABLE, TICOS_GPIO_MODE_INPUT 或 TICOS_GPIO_MODE_OUTPUT */
    TICOS_VAR(bool, level);         /**< GPIO 引脚状态，true: 拉高，false: 拉低 */
TICOS_DEV_CLASS_END();

#ifdef __TICOS_CONFIG_IMPORT

/************************************************************************
 * 此函数为自动生成的内部函数，请不要更改函数内容
 ************************************************************************/
int ticos_gpio_sync_from_cache(ticos_gpio_t* self) {
    ticos_sync_from_cache(self, level);
    return TICOS_OK;
}

/************************************************************************
 * 此函数为自动生成的内部函数，请不要更改函数内容
 ************************************************************************/
int ticos_gpio_post_to_cache(ticos_gpio_t* self) {
    ticos_post_to_cache(self, level);
    return TICOS_OK;
}

#endif

#ifdef __cplusplus
}
#endif

#endif // __TICOS_GPIO_H
