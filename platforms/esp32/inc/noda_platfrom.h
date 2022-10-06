#ifndef __NODA_PLATFORM_H
#define __NODA_PLATFORM_H

#include "noda_common.h"
#include "noda_internal.h"

void app_main(void) {
    noda_err_t rt = noda_startup();
    if (NODA_OK == rt) {
        while (noda_loop() == NODA_OK);
        noda_cleanup();
    }
}

#endif // __NODA-PLATFORM_H
