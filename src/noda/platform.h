#ifndef __NODA_PLATFORM_H
#define __NODA_PLATFORM_H

#include "noda/common.h"
#include "noda/internal.h"

void setup(void) {
    noda_startup();
}

void loop(void) {
    noda_loop();
}

#endif // __NODA_PLATFORM_H
