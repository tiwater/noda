#ifndef __NODA_PLATFORM_H
#define __NODA_PLATFORM_H

#include "noda/common.h"
#include "noda/internal.h"

void setup() {
    noda_startup();
}

void loop() {
    if (NODA_OK != noda_loop()) {
        noda_cleanup();
    }
}

#endif // __NODA_PLATFORM_H
