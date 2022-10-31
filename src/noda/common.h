#ifndef __NODA_COMMON_H
#define __NODA_COMMON_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>

#define NODA_UNUSED(x) (void) x

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t ticos_pin_t;

typedef enum {
    NODA_FAIL = -1,
    NODA_OK,
} ticos_err_t;

#ifdef __cplusplus
}
#endif

#endif // __NODA_COMMON_H
