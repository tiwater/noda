#ifndef __TICOS_FRAMEWORK_H
#define __TICOS_FRAMEWORK_H

#include "ticos/common.h"
#include "ticos/internal.h"

#ifdef __cplusplus
extern "C" {
#endif

void ticos_register_onexit(int (*onexit) (void));

int ticos_onboot(void);

int ticos_onloop(void);

#ifdef __cplusplus
}
#endif

#include <ticos/platform.h>

#endif // __TICOS_FRAMEWORK_H
