#include "noda_device.h"
#include "noda_log.h"

int noda_device_service_init(int c, noda_device_t** devs) {
    for (int i = 0; i < c; ++i) {
        noda_logd("device %d:%s at %p", i, devs[i]->name, (void*)devs[i]);
    }
    return NODA_OK;
}
