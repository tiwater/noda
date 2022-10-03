#ifndef __NODA_COMMON_H
#define __NODA_COMMON_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define NODA_UNUSED(x) (void) x

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NODA_OK,
    NODA_FAIL,
} noda_err_t;

#ifdef __cplusplus
}
#endif

#endif // __NODA_COMMON_H
