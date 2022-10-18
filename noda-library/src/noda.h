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

#ifdef __cplusplus
}
#endif

#include <noda/platform.h>

#endif // __NODA_H
