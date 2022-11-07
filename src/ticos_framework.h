#ifndef __TICOS_FRAMEWORK_H
#define __TICOS_FRAMEWORK_H

#include "ticos/common.h"
#include "ticos/internal.h"
#include "ticos/bus_center.h"
#include "ticos/device_center.h"

#ifndef TICOS_HEARTBEAT_MILLIS
#define TICOS_HEARTBEAT_MILLIS 200
#endif

#ifdef __cplusplus
extern "C" {
#endif

void ticos_register_onexit(int (*onexit) (void));

#define ticos_onboot \
    ticos_onboot_internal(void); \
    uint8_t ticos_bus_center_nbus(void) { return TICOS_NBUS; } \
    ticos_bus_t* ticos_bus_list[TICOS_NBUS]; \
    struct ticos_device_list_t ticos_device_list = { 0 }; \
    int ticos_onboot_internal

int ticos_onloop(void);

#ifdef __cplusplus
}
#endif

#include <ticos/platform.h>

#endif // __TICOS_FRAMEWORK_H
