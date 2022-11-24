#ifndef __TICOS_BUS_CENTER_INTERNAL_H
#define __TICOS_BUS_CENTER_INTERNAL_H

#undef TICOS_BUS_BEGIN
#undef TICOS_BUS_END
#undef TICOS_BUS

#define TICOS_BUS_BEGIN \
    ticos_bus_t* ticos_bus_list[] = {

#define TICOS_BUS_END \
        NULL, \
    };

#define TICOS_BUS(id, type, ...) \
        (ticos_bus_t * const) id,

#endif // __TICOS_BUS_CENTER_INTERNAL_H
