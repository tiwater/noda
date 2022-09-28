#ifndef __NODA_H
#define __NODA_H

//#include "noda_common.h"
//#include "noda_internal.h"


#ifdef __cplusplus
extern "C" {
#endif

int noda_startup(void);
//int noda_startup(int argc, const char** argv);
int noda_cleanup(void);
int noda_onloop(void);

#ifdef NODA_USE_CUSTOM_APP_ENTRY
int main(int argc, const char** argv) {
    int rt = noda_startup();
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
