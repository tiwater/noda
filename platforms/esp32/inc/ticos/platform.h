#ifndef __TICOS_PLATFORM_H
#define __TICOS_PLATFORM_H

#include "ticos/common.h"
#include "ticos/internal.h"

void app_main(void) {
    ticos_err_t rt = ticos_boot();
    if (TICOS_OK == rt) {
        while (ticos_loop() == TICOS_OK);
    }
}

#endif // __TICOS_PLATFORM_H
