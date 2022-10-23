#ifndef __NODA_BUS_CENTER_H
#define __NODA_BUS_CENTER_H

#include "noda/common.h"
#include "noda/bus.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NODA_BUS_ID_BEGIN \
    enum noda_bus_id_t {

#define NODA_BUS_ID_END \
    NODA_NBUS, \
    };

#define NODA_BUS_ADD(_id, bus, ...) \
    do { \
        static bus##_t bus##_id = { \
            NODA_BUS_SET_VTABLE(bus), .name = #_id, __VA_ARGS__ \
        }; \
        noda_bus_list[_id] = (noda_bus_t*)&bus##_id; \
    } while (0)

int noda_bus_center_startup(void);
int noda_bus_center_cleanup(void);
uint8_t noda_bus_center_nbus(void);

extern noda_bus_t* noda_bus_list[];

#define noda_bus(id)        (noda_bus_list[id])

#define noda_bus_name(id)   (noda_bus_list[id]->name)

#define noda_bus_opened(id) (noda_bus_list[id]->opened)

#ifdef __cplusplus
}
#endif

#endif // __NODA_BUS_CENTER_H
