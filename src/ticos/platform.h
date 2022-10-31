#ifndef __TICOS_PLATFORM_H
#define __TICOS_PLATFORM_H

#include "ticos/common.h"
#include "ticos/internal.h"
#include <Arduino.h>

void setup(void) {
    ticos_boot();
}

void loop(void) {
    ticos_loop();
}

#endif // __TICOS_PLATFORM_H
