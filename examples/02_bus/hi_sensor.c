#include "hi_sensor.h"
#include "noda_log.h"

/*************************************************************************
  * hi_sensor_open：hi_sensor必须实现的类成员函数，负责设备“打开”操作，
  * 后期可以通过代码模板自动生成函数体，不需要用户手动创建
  * @param self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int hi_sensor_open(hi_sensor_t* self) {
    NODA_UNUSED(self);
    return NODA_OK;
}

/*************************************************************************
  * hi_sensor_close：hi_sensor必须实现的类成员函数，负责设备“关闭”操作，
  * 后期可以通过代码模板自动生成函数体，不需要用户手动创建
  * @param self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int hi_sensor_close(hi_sensor_t* self) {
    NODA_UNUSED(self);
    return NODA_OK;
}

/*************************************************************************
  * hi_sensor_power_mode_changed：hi_sensor必须实现的类成员函数，
  * 系统改变“电源模式”时被动触发，
  * 后期可以通过代码模板自动生成函数体，不需要用户手动创建
  * @param self 类实例
  * @param mode 更改后的电源模式
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int hi_sensor_power_mode_changed(hi_sensor_t* self, noda_power_mode_t mode) {
    NODA_UNUSED(self);
    NODA_UNUSED(mode);
    return NODA_OK;
}

/*************************************************************************
  * hi_sensor_sync_from_cache：hi_sensor必须实现的类成员函数，
  * 负责设备数据从缓存复制到应用层的复制操作，
  * 后期可以通过代码模板自动生成函数体，不需要用户手动创建
  * @param self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int hi_sensor_sync_from_cache(hi_sensor_t* self) {
    noda_sync_from_cache(self, x); // 此处函数体为数据同步接口
    noda_sync_from_cache(self, y); // 后期可以通过代码模板自动生成
    noda_sync_from_cache(self, z); // 不需要用户手动填写
    return NODA_OK;
}

/*************************************************************************
  * hi_sensor_post_to_cache：hi_sensor必须实现的类成员函数，
  * 负责设备数据从应用层到缓存的复制操作，
  * 后期可以通过代码模板自动生成函数体，不需要用户手动创建
  * @param self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int hi_sensor_post_to_cache(hi_sensor_t* self) {
    noda_post_to_cache(self, x); // 此处函数体为数据同步接口
    noda_post_to_cache(self, y); // 后期可以通过代码模板自动生成
    noda_post_to_cache(self, z); // 不需要用户手动填写
    return NODA_OK;
}

/*************************************************************************
  * hi_sensor_sync_cache_from_dev：hi_sensor必须实现的类成员函数，
  * 负责设备数据从传感器到缓存的获取操作，
  * 后期可以通过代码模板自动生成函数体，不需要用户手动创建
  * @param self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int hi_sensor_sync_cache_from_dev(hi_sensor_t* self) {
    static float count;
    noda_setcache(self, x, count++); // noda_setcache调用需要用户手动调用
    noda_setcache(self, y, count++); // 用户需要调用传感器提供的接口获取数值
    noda_setcache(self, z, count++); // 再通过noda_setcache接口填充到缓存中
    return NODA_OK;
}

/*************************************************************************
  * hi_sensor_post_cache_to_dev：hi_sensor必须实现的类成员函数，
  * 负责设备数据从缓存到传感器的提交操作，
  * 后期可以通过代码模板自动生成函数体，不需要用户手动创建
  * @param self 类实例
  * @return 返回操作结果 NODA_OK: 成功, NODA_FAIL: 失败
  ************************************************************************/
int hi_sensor_post_cache_to_dev(hi_sensor_t* self) {
#if 0
    if (noda_cacheisdirty(self, adc)) {     // 检查缓存数值已经被应用层更新
        int adc = noda_getcache(self, adc); // 从缓存获取数值
        noda_logd("%s adc update to %d", self->name, adc); // TODO 提交到设备
    }
#else
    NODA_UNUSED(self);
#endif
    return NODA_OK;
}
