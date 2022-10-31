#ifndef __NODA_PLATFORM_H
#define __NODA_PLATFORM_H

#include "noda/common.h"
#include "noda/internal.h"
#include <Arduino.h>

void setup(void) {
    ticos_boot();
}

void loop(void) {
    ticos_loop();
}

#endif // __NODA_PLATFORM_H
