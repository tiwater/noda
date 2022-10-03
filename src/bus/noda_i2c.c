#include "bus/noda_i2c.h"
#include "noda_log.h"

int noda_i2c_open(noda_i2c_t* self) {
    self->opened = true;
    return NODA_OK;
}

int noda_i2c_close(noda_i2c_t* self) {
    self->opened = false;
    return NODA_OK;
}
