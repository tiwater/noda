#include "noda/time.h"
#include <sys/select.h>

static inline clock_t ticos_timenow(void) {
    return clock();
}

static inline clock_t ticos_timediff(clock_t t0, clock_t t1) {
    return (t0 < t1 ? 0 : LONG_MAX) + t1 - t0;
}

void ticos_delay(clock_t ms) {
    static clock_t prev, curr;

    clock_t timeout, millis;
    struct timeval tv;

    curr    = ticos_timenow();
    millis  = ticos_timediff(prev, curr);
    timeout = ms - millis;
    prev    = curr;

    if (timeout > 0) {
        tv.tv_sec = timeout / 1000;
        tv.tv_usec= (timeout % 1000) * 1000;
        select(0, NULL, NULL, NULL, &tv);
    }
}
