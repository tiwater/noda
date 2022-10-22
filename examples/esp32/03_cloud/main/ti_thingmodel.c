/*************************************************************************
  * @file ti_thingmodel.c 物模型代码文件
  * @generate date: 2022-10-19 16:42:13
  * 此文件为自动生成，请不要更改文件内容
  ************************************************************************/

#include "ti_thingmodel.h"
#include <noda/device_center.h>
#include "noda_iot.h"

bool ti_iot_prop_switch_send(void) {
    noda_iot_t* iot = noda_dev(0, noda_iot);
    return noda_cache_get(iot, prop_switch);
}

int ti_iot_prop_switch_recv(bool switch_) {
    noda_iot_t* iot = noda_dev(0, noda_iot);
    noda_cache_set(iot, prop_switch, switch_);
    return 0;
}

int ti_iot_prop_light_send(void) {
    noda_iot_t* iot = noda_dev(0, noda_iot);
    return noda_cache_get(iot, prop_light);
}

int ti_iot_prop_light_recv(int light) {
    noda_iot_t* iot = noda_dev(0, noda_iot);
    noda_cache_set(iot, prop_light, light);
    return 0;
}

const char* ti_iot_prop_DebugInfo_send(void) {
    noda_iot_t* iot = noda_dev(0, noda_iot);
    return noda_cache_get(iot, prop_DebugInfo);
}

int ti_iot_prop_DebugInfo_recv(const char* DebugInfo) {
    noda_iot_t* iot = noda_dev(0, noda_iot);
    noda_cache_set(iot, prop_DebugInfo, DebugInfo);
    return 0;
}

const ti_iot_telemetry_info_t ti_iot_telemetry_tab[] = {
};

const ti_iot_property_info_t ti_iot_property_tab[] = {
    { "switch", TICOS_IOT_VAL_TYPE_BOOLEAN,  ti_iot_prop_switch_send, ti_iot_prop_switch_recv },
    { "light", TICOS_IOT_VAL_TYPE_INTEGER,  ti_iot_prop_light_send, ti_iot_prop_light_recv },
    { "DebugInfo", TICOS_IOT_VAL_TYPE_STRING,  ti_iot_prop_DebugInfo_send, ti_iot_prop_DebugInfo_recv },
};

const ti_iot_command_info_t ti_iot_command_tab[] = {
};

const int ti_iot_telemetry_cnt = TICOS_IOT_TELEMETRY_MAX;
const int ti_iot_property_cnt = TICOS_IOT_PROPERTY_MAX;
const int ti_iot_command_cnt = TICOS_IOT_COMMAND_MAX;
