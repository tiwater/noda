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

int noda_onstart(void);
int noda_onclean(void);
int noda_onloop(void);

#ifndef NODA_USE_CUSTOM_APP_ENTRY
#include <noda_platform.h>
#endif

#ifdef __cplusplus
}
#endif

#endif // __NODA_H
