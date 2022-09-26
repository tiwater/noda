#ifndef __NODA_DEVICE_H
#define __NODA_DEVICE_H

#include "noda_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NODA_DEVICE_BASE \
    int (*on_config) (void* conf); \
    int (*on_open) (void); \
    int (*on_close) (void); \
    int (*on_power_mode_changed) (noda_power_mode_t mode); \
    int (*on_read) (int c, uint8_t* data); \
    int (*on_write) (int c, const uint8_t* data); \
    const char* name

typedef enum {
    NODA_POWER_MODE_UNKNOWN,
} noda_power_mode_t;

typedef struct {
    NODA_DEVICE_BASE;
} noda_device_t;

#ifdef __cplusplus
}
#endif

#endif // __NODA_DEVICE_H
