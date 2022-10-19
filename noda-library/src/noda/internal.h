#ifndef __NODA_INTERNAL_H
#define __NODA_INTERNAL_H

#include "noda/common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int noda_onstart(void);
extern int noda_onclean(void);
extern int noda_onloop(void);

int noda_startup(void);
int noda_loop_internal(clock_t millis);
#define noda_loop() noda_loop_internal(NODA_HEARTBEAT_MILLIS)

#ifdef __cplusplus
}
#endif

#endif // __NODA_INTERNAL_H
