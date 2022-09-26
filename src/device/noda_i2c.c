#include "noda_i2c.h"

int noda_i2c_open(noda_i2c_t* i2c) {
    if (noda_i2c_is_opened(i2c)) {
        return NODA_OK;
    }
    return NODA_FAIL;
}

int noda_i2c_close(noda_i2c_t* i2c) {
    if (!noda_i2c_is_opened(i2c)) {
        return NODA_OK;
    }
    return NODA_FAIL;
}

int noda_i2c_write(noda_i2c_t* i2c, uint8_t reg, const uint8_t data) {
    if (!noda_i2c_is_opened(i2c)) {
        return NODA_FAIL;
    }
    return NODA_OK;
}

int noda_i2c_read(noda_i2c_t* i2c, uint8_t reg, uint8_t* pdata, uint8_t len) {
    if (!noda_i2c_is_opened(i2c) || !pdata) {
        return NODA_FAIL;
    }
    return NODA_OK;
}
