#include "ticos/bus_center.h"
#include "ticos/log.h"

extern ticos_bus_t* ticos_bus_list[];

#define _has_bus() \
    (ticos_bus_list[0])

#define _foreach_bus(bus) \
    for (ticos_bus_t **l = ticos_bus_list, *bus = l[0]; bus; bus = *(l += 1))

int ticos_bus_center_startup(void) {
    if (_has_bus()) {
        ticos_logd("bus center startup");
        _foreach_bus(bus) {
            if (!bus->opened) {
                if (TICOS_OK == bus->open(bus)) {
                    ticos_logd("bus %s open", bus->name);
                } else {
                    ticos_loge("fail to open bus %s", bus->name);
                }
            }
        }
    }
    return TICOS_OK;
}

int ticos_bus_center_cleanup(void) {
    if (_has_bus()) {
        _foreach_bus(bus) {
            if (bus->opened) {
                if (TICOS_OK == bus->close(bus)) {
                    ticos_logd("bus %s close", bus->name);
                } else {
                    ticos_loge("fail to close bus %s", bus->name);
                }
            }
        }
        ticos_logd("bus center cleanup");
    }
    return TICOS_OK;
}
