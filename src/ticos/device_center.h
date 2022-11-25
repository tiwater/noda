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

#define TICOS_DEV_BEGIN
#define TICOS_DEV_END

#ifdef __TICOS_CONFIG_IMPORT
/**/
#define TICOS_DEV(id, type, ...) \
    type##_t _##type##id = { \
        TICOS_DEV_SET_VTABLE(type), .name = TICOS_STRINGIFY(id), __VA_ARGS__ \
    }; \
    static type##_t* const id = &_##type##id;
#else
/**/
#define TICOS_DEV(id, type, ...) \
    extern type##_t _##type##id; \
    static type##_t* const id = &_##type##id;
#endif

/**
  * @brief 通过设备 ID 检索 设备句柄
  * @param[in] id 设备 ID
  * @return 设备句柄
  */
#define ticos_dev(id)       (id)

/**
  * @brief 通过设备 ID 检索 设备名
  * @return 设备名
  */
#define ticos_dev_name(id)  (ticos_dev(id)->name)

#ifdef __cplusplus
}
#endif

#endif // __TICOS_DEVICE_CENTER_H
