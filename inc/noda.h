#ifndef __NODA_H
#define __NODA_H

#include "noda_common.h"
#include "noda_internal.h"
#include "noda_bus_center.h"
#include "noda_device_center.h"

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
#include "noda_platfrom.h"
#endif

#ifdef __cplusplus
}
#endif

#endif // __NODA_H
