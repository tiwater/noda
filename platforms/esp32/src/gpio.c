/*************************************************************************
  * @file noda_gpio
  * @brief 设备接口实现
  * @author
  * @date 2022-10-24 16:56:15
  * @copyright
  ************************************************************************/

#include "noda/device/gpio.h"

#include <driver/gpio.h>

/*************************************************************************
  * @fn noda_gpio_open
  * @brief 必须实现的类成员函数，负责设备“打开”操作，
  * @param[in] self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_gpio_open(noda_gpio_t* self) {
    gpio_config_t conf = {
        .pin_bit_mask = BIT64(self->pin),
        .mode = self->mode,
        .pull_up_en = GPIO_PULLUP_ENABLE,
    };
    gpio_config(&conf);
    return NODA_OK;
}

/*************************************************************************
  * @fn noda_gpio_close
  * @brief 必须实现的类成员函数，负责设备“关闭”操作，
  * @param[in] self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_gpio_close(noda_gpio_t* self) {
    gpio_reset_pin(self->pin);
    return NODA_OK;
}

/*************************************************************************
  * @fn noda_gpio_power_mode_changed
  * @brief 必须实现的类成员函数，系统改变“电源模式”时被动触发，
  * @param[in] self 类实例
  * @param[in] mode 更改后的电源模式
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_gpio_power_mode_changed(noda_gpio_t* self, noda_power_mode_t mode) {
    /* 填充代码内容后请删除NODA_UNUSED函数调用 */
    NODA_UNUSED(self);
    NODA_UNUSED(mode);
    return NODA_OK;
}

/*************************************************************************
  * @fn noda_gpio_sync_from_cache
  * @brief 必须实现的类成员函数，负责设备数据从缓存复制到应用层的复制操作
  * @attention 此函数为自动生成，请不要更改函数内容
  * @param[in] self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_gpio_sync_from_cache(noda_gpio_t* self) {
    noda_sync_from_cache(self, level);
    return NODA_OK;
}

/*************************************************************************
  * @fn noda_gpio_post_to_cache
  * @brief 必须实现的类成员函数，负责设备数据从应用层到缓存的复制操作
  * @attention 此函数为自动生成，请不要更改函数内容
  * @param[in] self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_gpio_post_to_cache(noda_gpio_t* self) {
    noda_post_to_cache(self, level);
    return NODA_OK;
}

/*************************************************************************
  * @fn noda_gpio_sync_cache_from_dev
  * @brief 必须实现的类成员函数，负责设备数据从传感器到缓存的获取操作
  * @param[in] self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_gpio_sync_cache_from_dev(noda_gpio_t* self) {
    if (self->mode & NODA_GPIO_MODE_INPUT) {
        bool lv = gpio_get_level(self->pin);
        noda_cache_set(self, level, lv);
    }
    return NODA_OK;
}

/*************************************************************************
  * @fn noda_gpio_post_cache_to_dev
  * @brief 必须实现的类成员函数，负责设备数据从缓存到传感器的提交操作
  * @param[in] self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_gpio_post_cache_to_dev(noda_gpio_t* self) {
    if ((self->mode & NODA_GPIO_MODE_OUTPUT)
        && noda_cache_isdirty(self, level)) {
       bool level = noda_cache_get(self, level);
       gpio_set_level(self->pin, level);
    }
    return NODA_OK;
}
