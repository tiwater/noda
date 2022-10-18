#ifndef __NODA_PLATFORM_H
#define __NODA_PLATFORM_H

#include "noda/common.h"
#include "noda/internal.h"

void setup(void) {
    noda_startup();
}

void loop(void) {
    if (NODA_OK != noda_loop()) {
        noda_cleanup();
    }
}

#endif // __NODA_PLATFORM_H
