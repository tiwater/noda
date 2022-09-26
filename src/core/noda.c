#include "noda_internal.h"

int noda_sleep(bool deep) {
    NODA_UNUSED(deep);
    return NODA_OK;
}

int noda_wakeup(void) {
    return NODA_OK;
}

int noda_sync(void) {
    return NODA_OK;
}

int noda_post(void) {
    return NODA_OK;
}
