#include "noda_ntc_sensor.h"

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

int noda_ntc_sensor_read(noda_ntc_sensor_t* self, int c, uint8_t* data) {
    NODA_UNUSED(self);
    NODA_UNUSED(c);
    NODA_UNUSED(data);
    return NODA_OK;
}

int noda_ntc_sensor_write(noda_ntc_sensor_t* self, int c, const uint8_t* data) {
    NODA_UNUSED(self);
    NODA_UNUSED(c);
    NODA_UNUSED(data);
    return NODA_OK;
}
