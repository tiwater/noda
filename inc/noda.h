#ifndef __NODA_H
#define __NODA_H

#include "noda_common.h"
#include "noda_internal.h"

#ifndef NODA_HEARTBEAT_MILLIS
#define NODA_HEARTBEAT_MILLIS 200
#endif

#ifdef __cplusplus
extern "C" {
#endif

int noda_onstart(int argc, const char** argv);
int noda_onclean(void);
int noda_onloop(void);

#ifndef NODA_USE_CUSTOM_APP_ENTRY
int main(int argc, const char** argv) {
    int rt = noda_startup(argc, argv);
    if (NODA_OK == rt) {
        while (NODA_OK == (rt = noda_loop()));
        rt = noda_cleanup();
    }
    return rt;
}
#endif

#ifdef __cplusplus
}
#endif

#endif // __NODA_H
