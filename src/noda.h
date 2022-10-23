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

#define noda_onboot \
    noda_onboot_internal(void); \
    uint8_t noda_bus_center_nbus(void) { return NODA_NBUS; } \
    noda_bus_t* noda_bus_list[NODA_NBUS]; \
    uint8_t noda_device_center_ndev(void) { return NODA_NDEV; } \
    noda_device_t* noda_device_list[NODA_NDEV]; \
    int noda_onboot_internal

int noda_onloop(void);

#ifdef __cplusplus
}
#endif

#include <noda/platform.h>

#endif // __NODA_H
