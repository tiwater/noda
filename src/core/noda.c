#include "noda/internal.h"
#include "noda/time.h"
#include "noda/bus_center.h"
#include "noda/device_center.h"
#include "noda/log.h"

static int g_ladder;

#define _LADDER_UP(l, job) \
    if (g_ladder <= l && NODA_OK == job()) { g_ladder = l; } else { break; }

#define _LADDER_DOWN(l, job) \
    if (g_ladder >= l && NODA_OK == job()) { g_ladder = l - 1; } else { break; }

int noda_boot(void) {
    if (NODA_OK == noda_onboot_internal()) do {
        _LADDER_UP(1, noda_bus_center_startup);
        _LADDER_UP(2, noda_device_center_startup);
    } while (0);
    return g_ladder >= 2 ? NODA_OK : NODA_FAIL;
}

static int noda_exit(void) {
    do {
        _LADDER_DOWN(2, noda_device_center_cleanup);
        _LADDER_DOWN(1, noda_bus_center_cleanup);
    } while (0);
    // TODO run noda_onexit here when user has registed onexit function
    return g_ladder <= 0 ? NODA_OK : NODA_FAIL;
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
