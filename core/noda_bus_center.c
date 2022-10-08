#include "noda_bus_center.h"
#include "noda_log.h"

int noda_bus_center_startup(void) {
    uint8_t nbus = noda_bus_center_nbus();
    if (nbus > 0) {
        noda_bus_t* const* buss = noda_bus_list;
        noda_bus_t* bus;
        noda_logd("bus center startup");
        for (int i = 0; i < nbus; ++i) {
            bus = buss[i];
            if (!bus->opened) {
                if (NODA_OK == bus->open(bus)) {
                    noda_logd("bus %d:%s open", i, bus->name);
                } else {
                    noda_loge("fail to open bus %d:%s", i, bus->name);
                }
            }
        }
    }
    return NODA_OK;
}

int noda_bus_center_cleanup(void) {
    uint8_t nbus = noda_bus_center_nbus();
    if (nbus > 0) {
        noda_bus_t* const* buss = noda_bus_list;
        noda_bus_t* bus;
        for (int i = 0; i < nbus; ++i) {
            bus = buss[i];
            if (bus->opened) {
                if (NODA_OK == bus->close(bus)) {
                    noda_logd("bus %d:%s close", i, bus->name);
                } else {
                    noda_loge("fail to close bus %d:%s", i, bus->name);
                }
            }
        }
        noda_logd("bus center cleanup");
    }
    return NODA_OK;
}
