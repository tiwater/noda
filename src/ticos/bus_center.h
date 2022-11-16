#ifndef __TICOS_BUS_CENTER_H
#define __TICOS_BUS_CENTER_H

#include "ticos/common.h"
#include "ticos/bus.h"

#ifdef __cplusplus
extern "C" {
#endif

int ticos_bus_center_startup(void);
int ticos_bus_center_cleanup(void);

#define TICOS_BUS_BEGIN
#define TICOS_BUS_END

#ifdef __TICOS_CONFIG_IMPORT
/**/
#define TICOS_BUS(id, type, ...) \
    type##_t id = { TICOS_BUS_SET_VTABLE(type), .name = #id, __VA_ARGS__ };
#else
/**/
#define TICOS_BUS(id, type, ...) \
    extern type##_t id;
#endif

// FIXME should be &id
#define ticos_bus(id)        (id)

#define ticos_bus_name(id)   (ticos_bus(id)->name)

#define ticos_bus_opened(id) (ticos_bus(id)->opened)

#ifdef __cplusplus
}
#endif

#endif // __TICOS_BUS_CENTER_H
