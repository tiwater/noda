#include "noda_ntc_sensor.h"
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

int noda_ntc_sensor_copy_cache(noda_ntc_sensor_t* self) {
    noda_copy(self, adc);
    return NODA_OK;
}

int noda_ntc_sensor_post_cache(noda_ntc_sensor_t* self) {
    noda_post(self, adc);
    return NODA_OK;
}
