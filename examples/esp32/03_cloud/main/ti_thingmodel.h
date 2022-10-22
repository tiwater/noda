/*************************************************************************
  * @file ti_thingmodel.h 物模型代码文件
  * @generate date: 2022-10-19 16:42:13
  * 此文件为自动生成，请不要更改文件内容
  ************************************************************************/

#ifndef __TI_THING_MODEL_H
#define __TI_THING_MODEL_H

#include <_ti_cfg_prefix.h>
#include <noda/common.h>
#include "ti_thingmodel_type.h"

typedef enum {
    TICOS_IOT_TELEMETRY_MAX,
} ti_iot_telemetry_t;

typedef enum {
    TICOS_IOT_PROPERTY_switch,
    TICOS_IOT_PROPERTY_light,
    TICOS_IOT_PROPERTY_DebugInfo,
    TICOS_IOT_PROPERTY_MAX,
} ti_iot_property_t;

typedef enum {
    TICOS_IOT_COMMAND_MAX,
} ti_iot_command_t;

bool ti_iot_property_switch_send(void);
int ti_iot_property_switch_recv(bool switch_);
int ti_iot_property_light_send(void);
int ti_iot_property_light_recv(int light);
const char* ti_iot_property_DebugInfo_send(void);
int ti_iot_property_DebugInfo_recv(const char* DebugInfo);

#include <_ti_cfg_suffix.h>

#endif // __TI_THING_MODEL_H
