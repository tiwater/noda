/*************************************************************************
  * @file noda_iot
  * @brief 设备接口实现
  * @author
  * @date 2022-10-24 16:56:15
  * @copyright
  ************************************************************************/

#include "noda_iot.h"
#include "noda/nil/wifi.h"
#include "noda_mqtt.h"

#include <ti_iot_api.h>

/*************************************************************************
  * @fn noda_iot_open
  * @brief 必须实现的类成员函数，负责设备“打开”操作，
  * @param[in] self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_iot_open(noda_iot_t* self) {
    noda_wifi_start_as_sta(self->ssid, self->pswd);
    noda_mqtt_start(self->fqdn, self->product_id, self->device_id);
    return NODA_OK;
}

/*************************************************************************
  * @fn noda_iot_close
  * @brief 必须实现的类成员函数，负责设备“关闭”操作，
  * @param[in] self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_iot_close(noda_iot_t* self) {
    /* 填充代码内容后请删除NODA_UNUSED函数调用 */
    NODA_UNUSED(self);
    noda_mqtt_stop();
    noda_wifi_stop();
    return NODA_OK;
}

/*************************************************************************
  * @fn noda_iot_power_mode_changed
  * @brief 必须实现的类成员函数，系统改变“电源模式”时被动触发，
  * @param[in] self 类实例
  * @param[in] mode 更改后的电源模式
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_iot_power_mode_changed(noda_iot_t* self, noda_power_mode_t mode) {
    /* 填充代码内容后请删除NODA_UNUSED函数调用 */
    NODA_UNUSED(self);
    NODA_UNUSED(mode);
    return NODA_OK;
}

/*************************************************************************
  * @fn noda_iot_sync_from_cache
  * @brief 必须实现的类成员函数，负责设备数据从缓存复制到应用层的复制操作
  * @attention 此函数为自动生成，请不要更改函数内容
  * @param[in] self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_iot_sync_from_cache(noda_iot_t* self) {
    noda_sync_from_cache(self, prop_switch);
    noda_sync_from_cache(self, prop_led);
    return NODA_OK;
}

/*************************************************************************
  * @fn noda_iot_post_to_cache
  * @brief 必须实现的类成员函数，负责设备数据从应用层到缓存的复制操作
  * @attention 此函数为自动生成，请不要更改函数内容
  * @param[in] self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_iot_post_to_cache(noda_iot_t* self) {
    noda_post_to_cache(self, prop_switch);
    noda_post_to_cache(self, prop_led);
    return NODA_OK;
}

/*************************************************************************
  * @fn noda_iot_sync_cache_from_dev
  * @brief 必须实现的类成员函数，负责设备数据从传感器到缓存的获取操作
  * @param[in] self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_iot_sync_cache_from_dev(noda_iot_t* self) {
    /* 填充代码内容后请删除NODA_UNUSED调用 */
    NODA_UNUSED(self);
    // 用法用例
    // bool lv = true;
    // noda_cache_set(self, level, lv); // 填充设备数据到相应缓存区
    return NODA_OK;
}

/*************************************************************************
  * @fn noda_iot_post_cache_to_dev
  * @brief 必须实现的类成员函数，负责设备数据从缓存到传感器的提交操作
  * @param[in] self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int noda_iot_post_cache_to_dev(noda_iot_t* self) {
    if (noda_cache_isdirty(self, prop_switch)
     || noda_cache_isdirty(self, prop_led)) {
        ti_iot_property_report();
    }
    return NODA_OK;
}
