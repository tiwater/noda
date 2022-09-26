#ifndef __NODA_DEVICE_H
#define __NODA_DEVICE_H

#include "noda_common.h"

#define NODA_DEVICE_LIST  \
    static noda_device_t* noda_device_list[] =

#define NODA_DEVICE_ADD(dev, ...) (noda_device_t*) &dev(__VA_ARGS__),

#define noda_device_init()  \
    noda_device_service_init(\
            sizeof(noda_device_list)/sizeof(noda_device_t*), \
            noda_device_list);

#define NODA_DEVICE_BASE \
    const char* name; \
    int (*on_config) (void* conf); \
    int (*on_open) (void); \
    int (*on_close) (void); \
    int (*on_power_mode_changed) (noda_power_mode_t mode); \
    int (*on_read) (int c, uint8_t* data); \
    int (*on_write) (int c, const uint8_t* data)

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NODA_POWER_MODE_UNKNOWN,
} noda_power_mode_t;

typedef struct {
    NODA_DEVICE_BASE;
} noda_device_t;

int noda_device_service_init(int c, noda_device_t** devs);

#ifdef __cplusplus
}
#endif

#endif // __NODA_DEVICE_H
