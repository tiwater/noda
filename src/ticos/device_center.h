#ifndef __TICOS_DEVICE_CENTER_H
#define __TICOS_DEVICE_CENTER_H

#include "ticos/common.h"
#include "ticos/device.h"

#ifdef __cplusplus
extern "C" {
#endif

int ticos_device_center_startup(void);
int ticos_device_center_cleanup(void);
int ticos_device_center_sync(void);
int ticos_device_center_post(void);
int ticos_device_center_dump(void);
uint8_t ticos_device_center_ndev(void);

extern ticos_device_t* ticos_device_list[];

#define TICOS_DEV_ID_BEGIN \
    enum ticos_device_id_t {

#define TICOS_DEV_ID_END \
    TICOS_NDEV, \
    };

#define TICOS_DEV_ADD(_id, dev, ...) \
    do { \
        static dev##_t dev##_id = { \
            TICOS_DEV_SET_VTABLE(dev), .name = #_id, __VA_ARGS__ \
        }; \
        ticos_device_list[_id] = (ticos_device_t*)&dev##_id; \
    } while (0)

/**
  * @fn ticos_dev
  * @brief 通过设备 ID 检索 设备句柄
  * @param[in] id 设备 ID
  * @param[in] type 设备类型
  * @return 设备句柄
  */
#define ticos_dev(id, type)    \
    ((type##_t*)(ticos_device_list[id]))

/**
  * @fn ticos_dev_name
  * @brief 通过设备 ID 检索 设备名
  * @return 设备名
  */
#define ticos_dev_name(id)        \
    (ticos_device_list[id]->name)

/**
  * @fn ticos_dev_isdirty
  * @brief 判断设备实例的 public 成员变量是否有刷新
  * @param[in] id 设备 ID
  * @param[in] type 设备类型
  * @param[in] v 成员变量，仅接受实例的 public 成员变量
  * @return true：刷新，false：无刷新
  */
#define ticos_dev_isdirty(id, type, v)   \
    (((type##_t*) ticos_device_list[id])->_##v##_dirty)

/**
  * @fn ticos_dev_getval
  * @brief 获取设备实例的 public 成员变量值
  * @param[in] id 设备 ID
  * @param[in] type 设备类型
  * @param[in] v 成员变量，仅接受实例的 public 成员变量
  * @return 返回变量值
  */
#define ticos_dev_getval(id, type, v)  \
    (((type##_t*) ticos_device_list[id])->_##v##_var)

/**
  * @fn ticos_dev_setval
  * @brief 设置设备实例的 public 成员变量值
  * @param[in] self 设备 ID
  * @param[in] v 成员变量，仅接受实例的 public 成员变量
  * @param[in] d 待更新的变量值输入
  */
#define ticos_dev_setval(id, type, v, d) \
    (((type##_t*) ticos_device_list[id])->_##v##_var = d)

#ifdef __cplusplus
}
#endif

#endif // __TICOS_DEVICE_CENTER_H
