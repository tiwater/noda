/************************************************************************
 * @file ticos_iot
 * @brief 设备接口头文件
 * @author
 * @date 2022-11-01 08:35:39
 * @copyright
 ************************************************************************/

#ifndef __TICOS_IOT_H
#define __TICOS_IOT_H

#include "ticos/device.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 * ticos_iot 类，用于使用 WIFI 的 IOT 设备
 ************************************************************************/
TICOS_DEV_CLASS_BEGIN(ticos_iot);
    const char* ssid;               /**< WIFI ssid */
    const char* pswd;               /**< WIFI password */
    const char* fqdn;               /**< mqtt fqdn 完全限定的域名 */
    const char* product_id;         /**< mqtt 产品 id */
    const char* device_id;          /**< mqtt 设备 id */
    const char* secret_key;         /**< mqtt 设备 密钥 */
    TICOS_VAR(bool, prop_switch);   /**< 物模型可用属性：开关 */
    TICOS_VAR(bool, prop_led);      /**< 物模型可用属性：led灯 */
TICOS_DEV_CLASS_END();

#ifdef __TICOS_CONFIG_IMPORT

/************************************************************************
 * 此函数为自动生成的内部函数，请不要更改函数内容
 ************************************************************************/
int ticos_iot_sync_from_cache(ticos_iot_t* self) {
    ticos_sync_from_cache(self, prop_switch);
    ticos_sync_from_cache(self, prop_led);
    return TICOS_OK;
}

/************************************************************************
 * 此函数为自动生成的内部函数，请不要更改函数内容
 ************************************************************************/
int ticos_iot_post_to_cache(ticos_iot_t* self) {
    ticos_post_to_cache(self, prop_switch);
    ticos_post_to_cache(self, prop_led);
    return TICOS_OK;
}

#endif

#ifdef __cplusplus
}
#endif

#endif // __TICOS_IOT_H
