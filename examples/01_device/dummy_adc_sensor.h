/*************************************************************************
  * @class dummy_adc_sensor 头文件
  * @generate date: 2022-10-04 12:44:02
  ************************************************************************/

#ifndef __DUMMY_ADC_SENSOR_H
#define __DUMMY_ADC_SENSOR_H

#include "noda_device.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************
  * dummy_adc_sensor类定义
  ************************************************************************/
NODA_DEVICE_CLASS_BEGIN(dummy_adc_sensor);
    noda_pin_t pin;
    uint8_t chn;
    uint16_t vref;
    NODA_VAR(int, adc);
NODA_DEVICE_CLASS_END();

#ifdef __cplusplus
}
#endif

#endif // __DUMMY_ADC_SENSOR_H
