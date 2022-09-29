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
    int (*copy_cache) (struct cls* self); \
    int (*post_cache) (struct cls* self); \
    bool opened

#define NODA_DEVICE_SET_VTABLE(cls) \
    .open = cls##_open, \
    .close = cls##_close, \
    .power_mode_changed = cls##_power_mode_changed, \
    .copy_cache = cls##_copy_cache, \
    .post_cache = cls##_post_cache

#define NODA_DEVICE_CLASS_BEGIN(cls) \
    struct cls##_t; \
    typedef struct cls##_t cls##_t; \
    int cls##_open(cls##_t* self); \
    int cls##_close(cls##_t* self); \
    int cls##_power_mode_changed(cls##_t* self, noda_power_mode_t mode); \
    int cls##_copy_cache(cls##_t* self); \
    int cls##_post_cache(cls##_t* self); \
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
    ((self)->_##v##_dirty = ((self)->_##v##_var != d), (self)->_##v##_var = d)

#define noda_getcache(self, v) noda_get(self, v##_cache)

#define noda_setcache(self, v, d) noda_set(self, v##_cache, d)

#define noda_copy(self, v)                              \
    if ((self)->_##v##_var != (self)->_##v##_cache_var) \
        noda_set((self), v, (self)->_##v##_cache_var)

#define noda_post(self, v)                              \
    if ((self)->_##v##_cache_var != (self)->_##v##_var) \
        noda_set((self), v##_cache, (self)->_##v##_var)

#ifdef __cplusplus
}
#endif

#endif // __NODA_DEVICE_H
