#ifndef __NODA_BUS_H
#define __NODA_BUS_H

#include "noda_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NODA_BUS_VTABLE(cls) \
    int (*open) (struct cls* self); \
    int (*close) (struct cls* self); \
    const char* name; \
    bool opened

#define NODA_BUS_SET_VTABLE(cls) \
    .open = cls##_open, \
    .close = cls##_close

#define NODA_BUS_CLASS_BEGIN(cls) \
    struct cls##_t; \
    typedef struct cls##_t cls##_t; \
    int cls##_open(cls##_t* self); \
    int cls##_close(cls##_t* self); \
    struct cls##_t { \
        NODA_BUS_VTABLE(cls##_t)

#define NODA_BUS_CLASS_END() }

typedef struct noda_bus_t {
    NODA_BUS_VTABLE(noda_bus_t);
} noda_bus_t;

#ifdef __cplusplus
}
#endif

#endif // __NODA_BUS_H
