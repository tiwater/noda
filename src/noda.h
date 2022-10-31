#ifndef __NODA_H
#define __NODA_H

#include "noda/common.h"
#include "noda/internal.h"
#include "noda/bus_center.h"
#include "noda/device_center.h"

#ifndef NODA_HEARTBEAT_MILLIS
#define NODA_HEARTBEAT_MILLIS 200
#endif

#ifdef __cplusplus
extern "C" {
#endif

void ticos_register_onexit(int (*onexit) (void));

#define ticos_onboot \
    ticos_onboot_internal(void); \
    uint8_t ticos_bus_center_nbus(void) { return NODA_NBUS; } \
    ticos_bus_t* ticos_bus_list[NODA_NBUS]; \
    uint8_t ticos_device_center_ndev(void) { return NODA_NDEV; } \
    ticos_device_t* ticos_device_list[NODA_NDEV]; \
    int ticos_onboot_internal

int ticos_onloop(void);

#ifdef __cplusplus
}
#endif

#include <noda/platform.h>

#endif // __NODA_H
