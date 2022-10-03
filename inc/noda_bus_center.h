#ifndef __NODA_BUS_CENTER_H
#define __NODA_BUS_CENTER_H

#include "noda_common.h"
#include "noda_bus.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NODA_BUS_ID_MAP \
    enum noda_bus_id_t

#define NODA_BUS_LIST \
    uint8_t noda_bus_center_nbus(void) { return NODA_NBUS; } \
    noda_bus_t* const noda_bus_list[] =

#define NODA_BUS_ADD(_id, bus, ...) \
    [_id] = (noda_bus_t*) &((bus##_t) { \
        NODA_BUS_SET_VTABLE(bus), \
        .name = #_id, \
        __VA_ARGS__ \
    })

int noda_bus_center_startup(void);
int noda_bus_center_cleanup(void);
uint8_t noda_bus_center_nbus(void);

extern noda_bus_t* const noda_bus_list[];

#ifdef __cplusplus
}
#endif

#endif // __NODA_BUS_CENTER_H
