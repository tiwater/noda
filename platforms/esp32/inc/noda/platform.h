#ifndef __NODA_PLATFORM_H
#define __NODA_PLATFORM_H

#include "noda/common.h"
#include "noda/internal.h"

void app_main(void) {
    ticos_err_t rt = ticos_boot();
    if (NODA_OK == rt) {
        while (ticos_loop() == NODA_OK);
    }
}

#endif // __NODA_PLATFORM_H
