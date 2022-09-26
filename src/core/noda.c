#include "noda_internal.h"
#include "noda_utils.h"

int noda_sleep(bool deep) {
    NODA_UNUSED(deep);
    return NODA_OK;
}

int noda_wakeup(void) {
    return NODA_OK;
}

static int noda_sync(void) {
    return NODA_OK;
}

static int noda_post(void) {
    return NODA_OK;
}

int noda_loop_internal(clock_t millis) {
    int rt = NODA_OK;
    noda_throttle(millis);
    noda_sync();
    rt = noda_onloop();
    noda_post();
    return rt;
}
