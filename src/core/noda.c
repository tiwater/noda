#include "noda_internal.h"
#include "noda_utils.h"
#include "noda_device_center.h"

int noda_sleep(bool deep) {
    NODA_UNUSED(deep);
    return NODA_OK;
}

int noda_wakeup(void) {
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
