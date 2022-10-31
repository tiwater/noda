#ifndef __NODA_BUS_H
#define __NODA_BUS_H

#include "noda/common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NODA_BUS_VTABLE(cls) \
    int (*open) (struct cls* ); \
    int (*close) (struct cls*); \
    int (*read) (struct cls*, uint8_t, uint8_t, uint8_t*, size_t, uint16_t); \
    int (*write_byte) (struct cls*, uint8_t, uint8_t, uint8_t, uint16_t); \
    const char* name; \
    bool opened

#define NODA_BUS_SET_VTABLE(cls) \
    .open = cls##_open, \
    .close = cls##_close, \
    .read = cls##_read, \
    .write_byte = cls##_write_byte

#define NODA_BUS_CLASS_BEGIN(cls) \
    struct cls##_t; \
    typedef struct cls##_t cls##_t; \
    int cls##_open(cls##_t* self); \
    int cls##_close(cls##_t* self); \
    int cls##_read(cls##_t* self, uint8_t addr, uint8_t reg, uint8_t* data, size_t len, uint16_t wait_ms); \
    int cls##_write_byte(cls##_t* self, uint8_t addr, uint8_t reg, uint8_t data, uint16_t wait_ms); \
    struct cls##_t { \
        NODA_BUS_VTABLE(cls##_t)

#define NODA_BUS_CLASS_END() }

typedef struct ticos_bus_t {
    NODA_BUS_VTABLE(ticos_bus_t);
} ticos_bus_t;

#ifdef __cplusplus
}
#endif

#endif // __NODA_BUS_H
