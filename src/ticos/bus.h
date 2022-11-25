#ifndef __TICOS_BUS_H
#define __TICOS_BUS_H

#include "ticos/common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TICOS_BUS_VTABLE(cls) \
    int (* const open) (struct cls* ); \
    int (* const close) (struct cls*); \
    int (* const read) (struct cls*, uint8_t, uint8_t, uint8_t*, size_t, uint16_t); \
    int (* const write_byte) (struct cls*, uint8_t, uint8_t, uint8_t, uint16_t); \
    const char* name; \
    bool opened

#define TICOS_BUS_SET_VTABLE(cls) \
    .open = cls##_open, \
    .close = cls##_close, \
    .read = cls##_read, \
    .write_byte = cls##_write_byte

#define TICOS_BUS_CLASS_BEGIN(cls) \
    struct cls##_t; \
    typedef struct cls##_t cls##_t; \
    int cls##_open(cls##_t* self); \
    int cls##_close(cls##_t* self); \
    int cls##_read(cls##_t* self, uint8_t addr, uint8_t reg, uint8_t* data, size_t len, uint16_t wait_ms); \
    int cls##_write_byte(cls##_t* self, uint8_t addr, uint8_t reg, uint8_t data, uint16_t wait_ms); \
    struct cls##_t { \
        TICOS_BUS_VTABLE(cls##_t)

#define TICOS_BUS_CLASS_END() }

typedef struct ticos_bus_t {
    TICOS_BUS_VTABLE(ticos_bus_t);
} ticos_bus_t;

#ifdef __cplusplus
}
#endif

#endif // __TICOS_BUS_H
