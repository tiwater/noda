/************************************************************************
 * @file ticos_thingmodel.h
 * @brief 物模型接口头文件
 * @author
 * @details 此文件为自动生成，请不要更改文件内容
 * @date 2022-11-01 08:35:39
 * @copyright
 ************************************************************************/

#ifndef __TICOS_THING_MODEL_H
#define __TICOS_THING_MODEL_H

#include <ticos/common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    TICOS_TELEMETRY_MAX,
} ticos_telemetry_t;

typedef enum {
    TICOS_PROPERTY_switch,
    TICOS_PROPERTY_led,
    TICOS_PROPERTY_MAX,
} ticos_property_t;

typedef enum {
    TICOS_COMMAND_MAX,
} ticos_command_t;

bool ticos_property_switch_send(void);
int ticos_property_switch_recv(bool switch_);
bool ticos_property_led_send(void);
int ticos_property_led_recv(bool led_);

#ifdef __cplusplus
}
#endif

#endif // __TICOS_THING_MODEL_H
