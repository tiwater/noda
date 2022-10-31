#ifndef __NODA_BUS_CENTER_H
#define __NODA_BUS_CENTER_H

#include "noda/common.h"
#include "noda/bus.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NODA_BUS_ID_BEGIN \
    enum ticos_bus_id_t {

#define NODA_BUS_ID_END \
    NODA_NBUS, \
    };

#define NODA_BUS_ADD(_id, bus, ...) \
    do { \
        static bus##_t bus##_id = { \
            NODA_BUS_SET_VTABLE(bus), .name = #_id, __VA_ARGS__ \
        }; \
        ticos_bus_list[_id] = (ticos_bus_t*)&bus##_id; \
    } while (0)

int ticos_bus_center_startup(void);
int ticos_bus_center_cleanup(void);
uint8_t ticos_bus_center_nbus(void);

extern ticos_bus_t* ticos_bus_list[];

#define ticos_bus(id)        (ticos_bus_list[id])

#define ticos_bus_name(id)   (ticos_bus_list[id]->name)

#define ticos_bus_opened(id) (ticos_bus_list[id]->opened)

#ifdef __cplusplus
}
#endif

#endif // __NODA_BUS_CENTER_H
