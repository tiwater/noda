#ifndef __NODA_DEVICE_H
#define __NODA_DEVICE_H

#include "noda_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NODA_DEVICE_BASE(cls) \
    int (*open) (struct cls* self); \
    int (*close) (struct cls* self); \
    int (*power_mode_changed) (struct cls* self, noda_power_mode_t mode); \
    int (*read) (struct cls* self, int c, uint8_t* data); \
    int (*write) (struct cls* self, int c, const uint8_t* data); \
    const char* name

typedef enum {
    NODA_POWER_MODE_UNKNOWN,
} noda_power_mode_t;

typedef struct noda_device_t {
    NODA_DEVICE_BASE(noda_device_t);
} noda_device_t;

#ifdef __cplusplus
}
#endif

#endif // __NODA_DEVICE_H
