#ifndef __TICOS_INTERNAL_H
#define __TICOS_INTERNAL_H

#include "ticos/common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void ticos_register_onexit(int (*onexit) (void));
extern int ticos_onboot(void);
extern int ticos_onloop(void);

int ticos_boot(void);
int ticos_loop_internal(clock_t millis);
#define ticos_loop() ticos_loop_internal(TICOS_HEARTBEAT_MILLIS)

#ifdef __cplusplus
}
#endif

#endif // __TICOS_INTERNAL_H
