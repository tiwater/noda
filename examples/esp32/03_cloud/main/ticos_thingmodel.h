/*************************************************************************
  * @file ticos_thingmodel.h 物模型代码文件
  * @generate date: 2022-10-22 23:53:41
  * 此文件为自动生成，请不要更改文件内容
  ************************************************************************/

#ifndef __TICOS_THING_MODEL_H
#define __TICOS_THING_MODEL_H

#include <noda/common.h>

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
