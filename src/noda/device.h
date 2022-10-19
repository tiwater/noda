#ifndef __NODA_DEVICE_H
#define __NODA_DEVICE_H

#include "noda/common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NODA_DEVICE_VTABLE(cls) \
    int (*open) (struct cls* self); \
    int (*close) (struct cls* self); \
    int (*power_mode_changed) (struct cls* self, noda_power_mode_t mode); \
    int (*sync_from_cache) (struct cls* self); \
    int (*post_to_cache) (struct cls* self); \
    int (*sync_cache_from_dev) (struct cls* self); \
    int (*post_cache_to_dev) (struct cls* self); \
    const char* name; \
    bool opened

#define NODA_DEVICE_SET_VTABLE(cls) \
    .open = cls##_open, \
    .close = cls##_close, \
    .power_mode_changed = cls##_power_mode_changed, \
    .sync_from_cache = cls##_sync_from_cache, \
    .post_to_cache = cls##_post_to_cache, \
    .sync_cache_from_dev = cls##_sync_cache_from_dev, \
    .post_cache_to_dev = cls##_post_cache_to_dev

#define NODA_DEVICE_CLASS_BEGIN(cls) \
    struct cls##_t; \
    typedef struct cls##_t cls##_t; \
    int cls##_open(cls##_t* self); \
    int cls##_close(cls##_t* self); \
    int cls##_power_mode_changed(cls##_t* self, noda_power_mode_t mode); \
    int cls##_sync_from_cache(cls##_t* self); \
    int cls##_post_to_cache(cls##_t* self); \
    int cls##_sync_cache_from_dev(cls##_t* self); \
    int cls##_post_cache_to_dev(cls##_t* self); \
    struct cls##_t { \
        NODA_DEVICE_VTABLE(cls##_t)

#define NODA_DEVICE_CLASS_END() }

typedef enum {
    NODA_POWER_MODE_UNKNOWN,
} noda_power_mode_t;

typedef struct noda_device_t {
    NODA_DEVICE_VTABLE(noda_device_t);
} noda_device_t;

#define NODA_VAR(type, v)       \
    type _##v##_var;            \
    type _##v##_cache_var;      \
    bool _##v##_dirty;          \
    bool _##v##_cache_dirty

#define noda_isdirty(self, v)   \
    ((self)->_##v##_dirty)

#define noda_get(self, v)       \
    ((self)->_##v##_dirty = false, (self)->_##v##_var)

#define noda_set(self, v, d)    \
    if ((self)->_##v##_var != d) {  \
        (self)->_##v##_dirty = true;\
        (self)->_##v##_var = d;     \
    }

#define noda_iscachedirty(self, v)  \
    noda_isdirty((self), v##_cache)

#define noda_sync_from_cache(self, v)                       \
    if ((self)->_##v##_var != noda_get((self), v##_cache))  \
        noda_set((self), v, (self)->_##v##_cache_var)

#define noda_post_to_cache(self, v)                         \
    if ((self)->_##v##_cache_var != noda_get((self), v))    \
        noda_set((self), v##_cache, (self)->_##v##_var)

#define noda_cache_isdirty(self, v) \
    noda_isdirty((self), v##_cache)

#define noda_cache_set(self, v, d)    \
    noda_set((self), v##_cache, d)

#define noda_cache_get(self, v) \
    noda_get((self), v##_cache)

#ifdef __cplusplus
}
#endif

#endif // __NODA_DEVICE_H
