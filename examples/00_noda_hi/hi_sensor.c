#include "hi_sensor.h"
#include "noda_log.h"

int hi_sensor_open(hi_sensor_t* self) {
    NODA_UNUSED(self);
    return NODA_OK;
}

int hi_sensor_close(hi_sensor_t* self) {
    NODA_UNUSED(self);
    return NODA_OK;
}

int hi_sensor_power_mode_changed(hi_sensor_t* self, noda_power_mode_t mode) {
    NODA_UNUSED(self);
    NODA_UNUSED(mode);
    return NODA_OK;
}

int hi_sensor_sync_from_cache(hi_sensor_t* self) {
    noda_sync_from_cache(self, x);
    noda_sync_from_cache(self, y);
    noda_sync_from_cache(self, z);
    return NODA_OK;
}

int hi_sensor_post_to_cache(hi_sensor_t* self) {
    noda_post_to_cache(self, x);
    noda_post_to_cache(self, y);
    noda_post_to_cache(self, z);
    return NODA_OK;
}

int hi_sensor_sync_cache_from_dev(hi_sensor_t* self) {
    static float count;
    noda_setcache(self, x, count++);
    noda_setcache(self, y, count++);
    noda_setcache(self, z, count++);
    return NODA_OK;
}

int hi_sensor_post_cache_to_dev(hi_sensor_t* self) {
    NODA_UNUSED(self);
    return NODA_OK;
}
