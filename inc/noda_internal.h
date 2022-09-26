#ifndef __NODA_INTERNAL_H
#define __NODA_INTERNAL_H

#include "noda_common.h"
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

int noda_sleep(bool deep);
int noda_wakeup(void);
extern int noda_onloop(void);

void noda_throttle(clock_t ms);

int noda_loop_internal(clock_t millis);
#define noda_loop() noda_loop_internal(NODA_HEARTBEAT_MILLIS)

#ifdef __cplusplus
}
#endif

#endif // __NODA_INTERNAL_H
