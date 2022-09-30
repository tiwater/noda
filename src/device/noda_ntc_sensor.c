#include "device/noda_ntc_sensor.h"
#include "noda_log.h"

int noda_ntc_sensor_open(noda_ntc_sensor_t* self) {
    NODA_UNUSED(self);
    return NODA_OK;
}

int noda_ntc_sensor_close(noda_ntc_sensor_t* self) {
    NODA_UNUSED(self);
    return NODA_OK;
}

int noda_ntc_sensor_power_mode_changed(noda_ntc_sensor_t* self, noda_power_mode_t mode) {
    NODA_UNUSED(self);
    NODA_UNUSED(mode);
    return NODA_OK;
}

int noda_ntc_sensor_sync_from_cache(noda_ntc_sensor_t* self) {
    noda_sync_from_cache(self, adc);
    return NODA_OK;
}

int noda_ntc_sensor_post_to_cache(noda_ntc_sensor_t* self) {
    noda_post_to_cache(self, adc);
    return NODA_OK;
}

int noda_ntc_sensor_sync_cache_from_dev(noda_ntc_sensor_t* self) {
    static int count;
    noda_setcache(self, adc, count++);
    return NODA_OK;
}

int noda_ntc_sensor_post_cache_to_dev(noda_ntc_sensor_t* self) {
#if 0
    if (noda_cacheisdirty(self, adc)) {
        int adc = noda_getcache(self, adc);
        noda_logd("%s adc update to %d", self->name, adc);
    }
#else
    NODA_UNUSED(self);
#endif
    return NODA_OK;
}
