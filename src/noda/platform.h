#ifndef __NODA_PLATFORM_H
#define __NODA_PLATFORM_H

#include "noda/common.h"
#include "noda/internal.h"
#include <Arduino.h>

void setup(void) {
    noda_boot();
}

void loop(void) {
    noda_loop();
}

#endif // __NODA_PLATFORM_H
