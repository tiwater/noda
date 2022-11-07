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

extern struct ticos_device_list_t ticos_device_list;

#define TICOS_DEV_ID_BEGIN \
    struct ticos_device_list_t {

#define TICOS_DEV_ID_END \
        ticos_device_t* _END; \
    };

#define TICOS_DEV_ID(id, type) \
    type##_t* id

#define TICOS_DEV(id, type, ...) \
    do { \
        static type##_t id = { \
            TICOS_DEV_SET_VTABLE(type), .name = #id, __VA_ARGS__ \
        }; \
        ticos_device_list.id = &id; \
    } while (0)

/**
  * @brief 通过设备 ID 检索 设备句柄
  * @param[in] id 设备 ID
  * @return 设备句柄
  */
#define ticos_dev(id)    \
   (ticos_device_list.id)

/**
  * @brief 通过设备 ID 检索 设备名
  * @return 设备名
  */
#define ticos_dev_name(id)        \
    (ticos_dev(id)->name)

/**
  * @brief 判断设备实例的 public 成员变量是否有刷新
  * @param[in] id 设备 ID
  * @param[in] v 成员变量，仅接受实例的 public 成员变量
  * @return true：刷新，false：无刷新
  */
#define ticos_dev_isdirty(id, v)   \
    (ticos_dev(id)->_##v##_dirty)

/**
  * @brief 获取设备实例的 public 成员变量值
  * @param[in] id 设备 ID
  * @param[in] v 成员变量，仅接受实例的 public 成员变量
  * @return 返回变量值
  */
#define ticos_dev_getval(id, v)  \
    (ticos_dev(id)->_##v##_var)

/**
  * @brief 设置设备实例的 public 成员变量值
  * @param[in] self 设备 ID
  * @param[in] v 成员变量，仅接受实例的 public 成员变量
  * @param[in] d 待更新的变量值输入
  */
#define ticos_dev_setval(id, v, d) \
    (ticos_dev(id)->_##v##_var = d)

#ifdef __cplusplus
}
#endif

#endif // __TICOS_DEVICE_CENTER_H
