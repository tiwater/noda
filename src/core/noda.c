#include "noda_internal.h"
#include "noda_utils.h"
#include "noda_device_center.h"

int noda_startup(int argc, const char** argv) {
    int rt = noda_onstart(argc, argv);
    if (NODA_OK == rt) {
        rt = noda_device_center_startup();
    }
    return rt;
}

int noda_cleanup(void) {
    noda_device_center_cleanup();
    noda_onclean();
    return NODA_OK;
}

int noda_loop_internal(clock_t millis) {
    int rt = NODA_OK;
    noda_throttle(millis);
    noda_device_center_sync();
    rt = noda_onloop();
    noda_device_center_post();
    return rt;
}
