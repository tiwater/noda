#include "noda_internal.h"

#include <sys/select.h>
#include "noda_time.h"
#include "noda_log.h"

void noda_throttle(clock_t ms) {
    static clock_t prev, curr;

    clock_t timeout, millis;
    struct timeval tv;

    curr    = noda_timenow();
    millis  = noda_timediff(prev, curr);
    timeout = ms - millis;
    prev    = curr;

    if (timeout > 0) {
        tv.tv_sec = timeout / 1000;
        tv.tv_usec= (timeout % 1000) * 1000;
        select(0, NULL, NULL, NULL, &tv);
    }
}
