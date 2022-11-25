/************************************************************************
 * @file silan_sc7a20
 * @brief 设备接口实现
 * @author
 * @date 2022-10-24 16:56:15
 * @copyright
 ************************************************************************/

#include "silan_sc7a20.h"
#include <ticos/bus_center.h>

/**********sc7a20**********/
#define IIC_ADDR        0x19

#define _CHIP_ID_ADDR    (0x0F)
#define _CHIP_ID_VALUE   (0x11)

#define _CTRL1      (0x20)
#define _CTRL2      (0x21)
#define _CTRL3      (0x22)
#define _CTRL4      (0x23)
#define _CTRL5      (0x24)
#define _CTRL6      (0x25)
#define _REFERENCE  (0x26)
#define _STATUS     (0x27)

#define _OUT_X_L    (0x28)
#define _OUT_X_H    (0x29)
#define _OUT_Y_L    (0x2A)
#define _OUT_Y_H    (0x2B)
#define _OUT_Z_L    (0x2C)
#define _OUT_Z_H    (0x2D)
#define _FIFO_CTRL  (0x2E)
#define _FIFO_SRC   (0x2F)

#define _INT1_CFG   (0x30)
#define _INT1_SRC   (0x31)
#define _INT1_THS   (0x32)
#define _INT1_DUR   (0x33)
#define _INT2_CFG   (0x34)
#define _INT2_SRC   (0x35)
#define _INT2_THS   (0x36)
#define _INT2_DUR   (0x37)

#define _CLICK_CFG      (0x38)
#define _CLICK_SRC      (0x39)
#define _CLICK_THS      (0x3A)
#define _TIME_LIMIT     (0x3B)
#define _TIME_LATENCY   (0x3C)
#define _TIME_WINDOW    (0x3D)
#define _ACT_THS        (0x3E)
#define _ACT_DURATION   (0x3F)

// CTRL1 # SAMPLING FREQUENCY / OPTION DATA RATE
// [ODR3 ODR2 ODR1 ODR0 LPen Zen Yen Xen]
#define _ODR_MASK   (0x07)  // Zen, Yen, Xen set to 1 to enable
#define _LP_MASK    (0x08)  // Low Power
#define _ODR_OFF    (0x00)  // Power Down
#define _ODR_1HZ    (0x10)
#define _ODR_10HZ   (0x20)
#define _ODR_25HZ   (0x30)
#define _ODR_50HZ   (0x40)
#define _ODR_100HZ  (0x50)
#define _ODR_200HZ  (0x60)
#define _ODR_400HZ  (0x70)
#define _ODR_1600HZ (0x88)  // Low power mode (1.6 KHz)
#define _ODR_1250HZ (0x90)  // Normal working mode (1.25 kHz) / Low power mode (5 KHz)

// MECHANICAL CHARACTERISTICS
// SENSITIVITY
// X mg / (0x1 << 11) = x mg/level or digit (0x1 << 11 --> 12 bit but signed so 11)
#define _SO_2G  (( 2000.0) / (0x2 << 10))  // ~1 mg / digit
#define _SO_4G  (( 4000.0) / (0x2 << 10))  // ~2 mg / digit
#define _SO_8G  (( 8000.0) / (0x2 << 10))  // ~4 mg / digit
#define _SO_16G ((16000.0) / (0x2 << 10))  // ~8 mg / digit

enum silan_sc7a20_range_t {
    SILAN_SC7A20_RANGE_2G   = 2,
    SILAN_SC7A20_RANGE_4G   = 4,
    SILAN_SC7A20_RANGE_8G   = 8,
    SILAN_SC7A20_RANGE_16G  = 16,
};

static inline int _write_byte(silan_sc7a20_t* self, uint8_t reg, uint8_t data) {
    return ticos_bus(self->bus)->write_byte(ticos_bus(self->bus),
            self->addr, reg, data, self->rw_wait_ms);
}

static inline int _read(silan_sc7a20_t* self, uint8_t reg, uint8_t* data, size_t len) {
    return ticos_bus(self->bus)->read(ticos_bus(self->bus),
           self->addr, reg, data, len, self->rw_wait_ms);
}

static inline int _read_byte(silan_sc7a20_t* self, uint8_t reg, uint8_t* data) {
    return _read(self, reg, data, 1);
}

static float sb2accel(uint8_t msb, uint8_t lsb, uint8_t range) {
    int16_t temp = (((msb << 8) | lsb) >> 4) & 0xFFF;
    if (temp & 0x0800) { // 需要计算补码
        temp &= 0x07FF;
        temp = ~temp;
        temp = temp + 1;
        temp &= 0x07FF;
        temp = -temp;
    }
    return temp * range * 1000.0 / 2048;
}

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备“打开”操作，
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int silan_sc7a20_open(silan_sc7a20_t* self) {
    if (ticos_bus_opened(self->bus)) {
        if (!self->opened) {
            uint8_t id = 0;
            ticos_err_t err = _read_byte(self, _CHIP_ID_ADDR, &id);
            if (TICOS_OK == err && id == _CHIP_ID_VALUE) {
                err &= _write_byte(self, _CTRL1, 0x4F);   // 50Hz，低功耗，使能x, y, z轴
                err &= _write_byte(self, _CTRL2, 0x81);   // 中断事件自动复位，配置AOI1高通滤波
                err &= _write_byte(self, _CTRL3, 0x40);   // 在INT1 上 使能 AOI1 中断
                err &= _write_byte(self, _CTRL4, 0x98);   // +/-4G量程，高精度使能
                err &= _write_byte(self, _CTRL5, 0x88);   // 在INT1 上配置重载修调值, 锁存中断配置寄存器上指定的中断响应
                err &= _write_byte(self, _CTRL6, 0x00);
                err &= _write_byte(self, _INT1_CFG, 0x7F);// 在INT1 上配置3轴高低事件或者6D方向运动识别使能
                err &= _write_byte(self, _INT1_THS, 0x03);// 在INT1 上配置中断阈值为3
                err &= _write_byte(self, _INT1_DUR, 0x03);// 在INT1 上配置中断事件最小持续时间为8 单位步进/以ODR为时钟
                self->opened = (TICOS_OK == err);
            }
        }
    }
    return self->opened ? TICOS_OK : TICOS_FAIL;
}

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备“关闭”操作，
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int silan_sc7a20_close(silan_sc7a20_t* self) {
    // TODO
    self->opened = false;
    return TICOS_OK;
}

/************************************************************************
 * @brief 必须实现的类成员函数，系统改变“电源模式”时被动触发，
 * @param[in] self 类实例
 * @param[in] mode 更改后的电源模式
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int silan_sc7a20_power_mode_changed(silan_sc7a20_t* self, ticos_power_mode_t mode) {
    /* 填充代码内容后请删除TICOS_UNUSED函数调用 */
    TICOS_UNUSED(self);
    TICOS_UNUSED(mode);
    return TICOS_OK;
}

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备数据从传感器到缓存的获取操作
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int silan_sc7a20_sync_from_dev(silan_sc7a20_t* self) {
    uint8_t buf[6] = { 0 };
    uint8_t range = SILAN_SC7A20_RANGE_4G;
    ticos_err_t err = _read(self, _OUT_X_L | 0x80, buf, 6);
    if (TICOS_OK == err) {
        float x = sb2accel(buf[1], buf[0], range);
        float y = sb2accel(buf[3], buf[2], range);
        float z = sb2accel(buf[5], buf[4], range);

        ticos_cache_set(self, x, x);
        ticos_cache_set(self, y, y);
        ticos_cache_set(self, z, z);
    }
    return err;
}

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备数据从缓存到传感器的提交操作
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int silan_sc7a20_post_to_dev(silan_sc7a20_t* self) {
    /* 填充代码内容后请删除TICOS_UNUSED调用 */
    TICOS_UNUSED(self);
    // 用法用例
    // if (ticos_cache_isdirty(self, level)) {  // 检查缓存数值已经被应用层更新
    //    bool level = ticos_cache_get(self, level); // 从缓存获取数值
    //    ticos_logd("%s level update to %d", self->name, level); // 提交到设备
    // }
    return TICOS_OK;
}
