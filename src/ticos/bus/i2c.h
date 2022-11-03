#ifndef __TICOS_I2C_H
#define __TICOS_I2C_H

#include "ticos/bus.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************
  * ticos_i2c 类，用于配置 I2C 总线
  ************************************************************************/
TICOS_BUS_CLASS_BEGIN(ticos_i2c);
    const uint8_t       port;   /**< I2C 总线号 */
    const ticos_pin_t    sda;   /**< I2C 数据线 */
    const ticos_pin_t    scl;   /**< I2C 时钟线 */
    uint16_t            freq;   /**< I2C 总线频率 */
TICOS_BUS_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __TICOS_I2C_H
