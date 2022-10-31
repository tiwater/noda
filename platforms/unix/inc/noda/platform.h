#ifndef __NODA_PLATFORM_H
#define __NODA_PLATFORM_H

#include "noda/common.h"
#include "noda/internal.h"

int main(int argc, char** argv) {
    NODA_UNUSED(argc);
    NODA_UNUSED(argv);
    ticos_err_t rt = ticos_boot();
    if (NODA_OK == rt) {
        while (ticos_loop() == NODA_OK);
    }
    return rt;
}

#endif // __NODA_PLATFORM_H
