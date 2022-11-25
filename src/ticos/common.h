#ifndef __TICOS_COMMON_H
#define __TICOS_COMMON_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>

#define TICOS_UNUSED(x) (void) x

#define __TICOS_STRINGIFY_1(x...)   #x
#define TICOS_STRINGIFY(x...)       __TICOS_STRINGIFY_1(x)

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t ticos_pin_t;

typedef enum {
    TICOS_FAIL = -1,
    TICOS_OK,
} ticos_err_t;

#ifdef __cplusplus
}
#endif

#endif // __TICOS_COMMON_H
