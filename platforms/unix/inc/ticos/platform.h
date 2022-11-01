#ifndef __TICOS_PLATFORM_H
#define __TICOS_PLATFORM_H

#include "ticos/common.h"
#include "ticos/internal.h"

int main(int argc, char** argv) {
    TICOS_UNUSED(argc);
    TICOS_UNUSED(argv);
    ticos_err_t rt = ticos_boot();
    if (TICOS_OK == rt) {
        while (ticos_loop() == TICOS_OK);
    }
    return rt;
}

#endif // __TICOS_PLATFORM_H
