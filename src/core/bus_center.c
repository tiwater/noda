#include "ticos/bus_center.h"
#include "ticos/log.h"

int ticos_bus_center_startup(void) {
    uint8_t nbus = ticos_bus_center_nbus();
    if (nbus > 0) {
        ticos_bus_t* const* buss = ticos_bus_list;
        ticos_bus_t* bus;
        ticos_logd("bus center startup");
        for (int i = 0; i < nbus; ++i) {
            bus = buss[i];
            if (!bus->opened) {
                if (TICOS_OK == bus->open(bus)) {
                    ticos_logd("bus %d:%s open", i, bus->name);
                } else {
                    ticos_loge("fail to open bus %d:%s", i, bus->name);
                }
            }
        }
    }
    return TICOS_OK;
}

int ticos_bus_center_cleanup(void) {
    uint8_t nbus = ticos_bus_center_nbus();
    if (nbus > 0) {
        ticos_bus_t* const* buss = ticos_bus_list;
        ticos_bus_t* bus;
        for (int i = 0; i < nbus; ++i) {
            bus = buss[i];
            if (bus->opened) {
                if (TICOS_OK == bus->close(bus)) {
                    ticos_logd("bus %d:%s close", i, bus->name);
                } else {
                    ticos_loge("fail to close bus %d:%s", i, bus->name);
                }
            }
        }
        ticos_logd("bus center cleanup");
    }
    return TICOS_OK;
}
