#ifndef __NODA_INTERNAL_H
#define __NODA_INTERNAL_H

#include "noda_common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int noda_onstart(int argc, const char** argv);
extern int noda_onclean(void);
extern int noda_onloop(void);

int noda_startup(int argc, const char** argv);
int noda_cleanup(void);
int noda_loop_internal(clock_t millis);
#define noda_loop() noda_loop_internal(NODA_HEARTBEAT_MILLIS)

#ifdef __cplusplus
}
#endif

#endif // __NODA_INTERNAL_H
