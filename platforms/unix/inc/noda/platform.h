#ifndef __NODA_PLATFORM_H
#define __NODA_PLATFORM_H

#include "noda/common.h"
#include "noda/internal.h"

int main(int argc, char** argv) {
    NODA_UNUSED(argc);
    NODA_UNUSED(argv);
    noda_err_t rt = noda_startup();
    if (NODA_OK == rt) {
        while (noda_loop() == NODA_OK);
        noda_cleanup();
    }
    return rt;
}

#endif // __NODA-PLATFORM_H
