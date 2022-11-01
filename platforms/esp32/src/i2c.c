#include "ticos/bus/i2c.h"
#include "ticos/log.h"

#include <driver/i2c.h>

int ticos_i2c_open(ticos_i2c_t* self) {
    if (!self->opened) {
        i2c_config_t conf = {
            .mode           = I2C_MODE_MASTER,
            .sda_io_num     = self->sda,
            .sda_pullup_en  = GPIO_PULLUP_ENABLE,
            .scl_io_num     = self->scl,
            .scl_pullup_en  = GPIO_PULLUP_ENABLE,
            .master.clk_speed   = self->freq * 1000,
        };
        i2c_param_config(self->port, &conf);
        if (ESP_OK != i2c_driver_install(self->port, conf.mode, 0, 0, 0)) {
            ticos_loge("fail to open i2c %d", self->port);
            return TICOS_FAIL;
        }
        self->opened = true;
    }
    return TICOS_OK;
}

int ticos_i2c_close(ticos_i2c_t* self) {
    if (self->opened) {
        i2c_driver_delete(self->port);
        self->opened = false;
    }
    return TICOS_OK;
}

int ticos_i2c_read(ticos_i2c_t* self, uint8_t addr, uint8_t reg, uint8_t* data, size_t len, uint16_t wait_ms) {
    return ESP_OK == i2c_master_write_read_device(self->port,
            addr, &reg, 1, data, len, wait_ms / portTICK_PERIOD_MS)
        ? TICOS_OK : TICOS_FAIL;
}

int ticos_i2c_write_byte(ticos_i2c_t* self, uint8_t addr, uint8_t reg, uint8_t data, uint16_t wait_ms) {
    const uint8_t buf[] = { reg, data };
    return ESP_OK == i2c_master_write_to_device(self->port,
            addr, buf, sizeof(buf), wait_ms / portTICK_PERIOD_MS)
        ? TICOS_OK : TICOS_FAIL;
} 
