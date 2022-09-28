#ifndef __NODA_DEVICE_H
#define __NODA_DEVICE_H

#include "noda_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NODA_DEVICE_VTABLE(cls) \
    const char* name; \
    int (*open) (struct cls* self); \
    int (*close) (struct cls* self); \
    int (*power_mode_changed) (struct cls* self, noda_power_mode_t mode); \
    int (*sync) (struct cls* self); \
    int (*post) (struct cls* self); \
    int (*read) (struct cls* self, int c, uint8_t* data); \
    int (*write) (struct cls* self, int c, const uint8_t* data); \
    bool opened

#define NODA_DEVICE_SET_VTABLE(cls) \
    .open = cls##_open, \
    .close = cls##_close, \
    .power_mode_changed = cls##_power_mode_changed, \
    .sync = cls##_sync, \
    .post = cls##_post, \
    .read = cls##_read, \
    .write = cls##_write

#define NODA_DEVICE_CLASS_BEGIN(cls) \
    struct cls##_t; \
    typedef struct cls##_t cls##_t; \
    int cls##_open(cls##_t* self); \
    int cls##_close(cls##_t* self); \
    int cls##_power_mode_changed(cls##_t* self, noda_power_mode_t mode); \
    int cls##_sync(cls##_t* self); \
    int cls##_post(cls##_t* self); \
    int cls##_read(cls##_t* self, int c, uint8_t* data); \
    int cls##_write(cls##_t* self, int c, const uint8_t* data); \
    struct cls##_t { \
        NODA_DEVICE_VTABLE(cls##_t)

#define NODA_DEVICE_CLASS_END() }

typedef enum {
    NODA_POWER_MODE_UNKNOWN,
} noda_power_mode_t;

typedef struct noda_device_t {
    NODA_DEVICE_VTABLE(noda_device_t);
} noda_device_t;

#ifdef __cplusplus
}
#endif

#endif // __NODA_DEVICE_H
