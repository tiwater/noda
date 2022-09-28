#ifndef __NODA_INTERNAL_H
#define __NODA_INTERNAL_H

#include "noda_common.h"
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NODA_HEARTBEAT_MILLIS
#define NODA_HEARTBEAT_MILLIS 200
#endif

int noda_sleep(bool deep);
int noda_wakeup(void);
extern int noda_onloop(void);

int noda_loop_internal(clock_t millis);
#define noda_loop() noda_loop_internal(NODA_HEARTBEAT_MILLIS)

#ifdef __cplusplus
}
#endif

#endif // __NODA_INTERNAL_H
