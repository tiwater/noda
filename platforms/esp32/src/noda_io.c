/*************************************************************************
  * @class noda_io 代码文件
  * @generate date: 2022-10-06 21:35:04
  ************************************************************************/

#include "noda_io.h"

#include <driver/gpio.h>

#include "noda_log.h"

/*************************************************************************
  * noda_io_open：noda_io必须实现的类成员函数，负责设备“打开”操作，
  * @param self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_io_open(noda_io_t* self) {
    gpio_config_t conf = {
        .pin_bit_mask = BIT64(self->pin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
    };
    gpio_config(&conf);
    return NODA_OK;
}

/*************************************************************************
  * noda_io_close：noda_io必须实现的类成员函数，负责设备“关闭”操作，
  * @param self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_io_close(noda_io_t* self) {
    gpio_reset_pin(self->pin);
    return NODA_OK;
}

/*************************************************************************
  * noda_io_power_mode_changed：noda_io必须实现的类成员函数，
  * 系统改变“电源模式”时被动触发，
  * @param self 类实例
  * @param mode 更改后的电源模式
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_io_power_mode_changed(noda_io_t* self, noda_power_mode_t mode) {
    /* 填充代码内容后请删除NODA_UNUSED函数调用 */
    NODA_UNUSED(self);
    NODA_UNUSED(mode);
    return NODA_OK;
}

/*************************************************************************
  * noda_io_sync_from_cache：noda_io必须实现的类成员函数，
  * 负责设备数据从缓存复制到应用层的复制操作，
  * 此函数为自动生成，请不要更改函数内容
  * @param self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_io_sync_from_cache(noda_io_t* self) {
    noda_sync_from_cache(self, level);
    return NODA_OK;
}

/*************************************************************************
  * noda_io_post_to_cache：noda_io必须实现的类成员函数，
  * 负责设备数据从应用层到缓存的复制操作，
  * 此函数为自动生成，请不要更改函数内容
  * @param self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_io_post_to_cache(noda_io_t* self) {
    noda_post_to_cache(self, level);
    return NODA_OK;
}

/*************************************************************************
  * noda_io_sync_cache_from_dev：noda_io必须实现的类成员函数，
  * 负责设备数据从传感器到缓存的获取操作，
  * @param self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_io_sync_cache_from_dev(noda_io_t* self) {
    bool lv = gpio_get_level(self->pin);
    noda_cache_set(self, level, lv); // 填充设备数据到相应缓存区
    return NODA_OK;
}

/*************************************************************************
  * noda_io_post_cache_to_dev：noda_io必须实现的类成员函数，
  * 负责设备数据从缓存到传感器的提交操作，
  * @param self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_io_post_cache_to_dev(noda_io_t* self) {
    /* 填充代码内容后请删除NODA_UNUSED调用 */
    NODA_UNUSED(self);
    // 用法用例
    // if (noda_cache_isdirty(self, level)) {  // 检查缓存数值已经被应用层更新
    //    bool level = noda_cache_get(self, level); // 从缓存获取数值
    //    noda_logd("%s level update to %d", self->name, level); // 提交到设备
    // }
    return NODA_OK;
}
