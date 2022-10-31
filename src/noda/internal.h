#ifndef __NODA_INTERNAL_H
#define __NODA_INTERNAL_H

#include "noda/common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void ticos_register_onexit(int (*onexit) (void));
extern int ticos_onboot_internal(void);
extern int ticos_onloop(void);

int ticos_boot(void);
int ticos_loop_internal(clock_t millis);
#define ticos_loop() ticos_loop_internal(NODA_HEARTBEAT_MILLIS)

#ifdef __cplusplus
}
#endif

#endif // __NODA_INTERNAL_H
