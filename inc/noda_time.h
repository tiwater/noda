#ifndef __NODA_TIME_H
#define __NODA_TIME_H

#include "noda_common.h"
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline clock_t noda_timenow(void) {
    return clock();
}

static inline clock_t noda_timediff(clock_t t0, clock_t t1) {
    return (t0 < t1 ? 0 : LONG_MAX) + t1 - t0;
}

#ifdef __cplusplus
}
#endif

#endif // __NODA_TIME_H
