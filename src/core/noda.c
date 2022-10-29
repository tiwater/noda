#include "noda/internal.h"
#include "noda/time.h"
#include "noda/bus_center.h"
#include "noda/device_center.h"
#include "noda/log.h"

int (*s_onexit) (void);

static int s_ladder;

#define _LADDER_UP(l, job) \
    if (s_ladder <= l && NODA_OK == (job)) { s_ladder = l; } else { break; }

#define _LADDER_DOWN(l, job) \
    if (s_ladder >= l && NODA_OK == (job)) { s_ladder = l - 1; } else { break; }

int noda_boot(void) {
    do {
        _LADDER_UP(1, noda_onboot_internal());
        _LADDER_UP(2, noda_bus_center_startup());
        _LADDER_UP(3, noda_device_center_startup());
    } while (0);
    return s_ladder >= 3 ? NODA_OK : NODA_FAIL;
}

void noda_register_onexit(int (*onexit) (void)) {
    s_onexit = onexit;
}

static int noda_onexit_internal(void) {
    if (s_onexit) {
        return s_onexit();
    }
    return NODA_OK;
}

static int noda_exit(void) {
    do {
        _LADDER_DOWN(3, noda_device_center_cleanup());
        _LADDER_DOWN(2, noda_bus_center_cleanup());
        _LADDER_DOWN(1, noda_onexit_internal());
    } while (0);
    return s_ladder <= 0 ? NODA_OK : NODA_FAIL;
}

int noda_loop_internal(clock_t millis) {
    int rt = NODA_OK;
    noda_delay(millis);
    noda_device_center_sync();
    rt = noda_onloop();
    noda_device_center_post();
    if (rt != NODA_OK) {
        noda_exit();
    }
    return rt;
}
