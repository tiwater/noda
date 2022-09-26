#ifndef __NODA_I2C_H
#define __NODA_I2C_H

#include "noda_common.h"

typedef struct {
    uint8_t sda;
    uint8_t scl;
    uint8_t addr;
    uint8_t freq;
    bool opened;
} noda_i2c_t;

#define NODA_I2C_CONF(_sda, _scl, _addr, _freq) { \
    .sda = (_sda); \
    .scl = (_scl); \
    .addr= (_addr);\
    .freq= (_freq);\
}

static inline bool noda_i2c_is_opened(noda_i2c_t* i2c) {
    return i2c && i2c->opened;
}
int noda_i2c_open(noda_i2c_t* i2c);
int noda_i2c_close(noda_i2c_t* i2c);
int noda_i2c_write(noda_i2c_t* i2c, uint8_t reg, const uint8_t data);
int noda_i2c_read(noda_i2c_t* i2c, uint8_t reg, uint8_t* pdata, uint8_t len);

#endif // __NODA_I2C_H
