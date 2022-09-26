#ifndef __NODA_INTERNAL_H
#define __NODA_INTERNAL_H

#include "noda_common.h"
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

int noda_sleep(bool deep);
int noda_wakeup(void);

int noda_sync(void);
int noda_post(void);

void noda_throttle(clock_t ms);

#ifdef __cplusplus
}
#endif

#endif // __NODA_INTERNAL_H
