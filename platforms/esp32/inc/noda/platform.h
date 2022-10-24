#ifndef __NODA_PLATFORM_H
#define __NODA_PLATFORM_H

#include "noda/common.h"
#include "noda/internal.h"

void app_main(void) {
    noda_err_t rt = noda_boot();
    if (NODA_OK == rt) {
        while (noda_loop() == NODA_OK);
    }
}

#endif // __NODA_PLATFORM_H
