#include "ticos/internal.h"
#include "ticos/bus_center.h"
#include "ticos/device_center.h"
#include "ticos/time.h"
#include "ticos/log.h"

int (*s_onexit) (void);

static int s_ladder;

#define _LADDER_UP(l, job) \
    if (s_ladder <= l && TICOS_OK == (job)) { s_ladder = l; } else { break; }

#define _LADDER_DOWN(l, job) \
    if (s_ladder >= l && TICOS_OK == (job)) { s_ladder = l - 1; } else { break; }

int ticos_boot(void) {
    do {
        _LADDER_UP(1, ticos_onboot());
        _LADDER_UP(2, ticos_bus_center_startup());
        _LADDER_UP(3, ticos_device_center_startup());
    } while (0);
    return s_ladder >= 3 ? TICOS_OK : TICOS_FAIL;
}

void ticos_register_onexit(int (*onexit) (void)) {
    s_onexit = onexit;
}

static int ticos_onexit_internal(void) {
    if (s_onexit) {
        return s_onexit();
    }
    return TICOS_OK;
}

static int ticos_exit(void) {
    do {
        _LADDER_DOWN(3, ticos_device_center_cleanup());
        _LADDER_DOWN(2, ticos_bus_center_cleanup());
        _LADDER_DOWN(1, ticos_onexit_internal());
    } while (0);
    return s_ladder <= 0 ? TICOS_OK : TICOS_FAIL;
}

int ticos_loop_internal(clock_t millis) {
    int rt = TICOS_OK;
    ticos_delay(millis);
    ticos_device_center_sync();
    rt = ticos_onloop();
    ticos_device_center_post();
    if (rt != TICOS_OK) {
        ticos_exit();
    }
    return rt;
}
