#ifndef __TICOS_DEVICE_CENTER_H
#define __TICOS_DEVICE_CENTER_H

#include "ticos/common.h"
#include "ticos/device.h"

#ifdef __cplusplus
extern "C" {
#endif

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

int ticos_device_center_startup(void);
int ticos_device_center_cleanup(void);
int ticos_device_center_sync(void);
int ticos_device_center_post(void);
int ticos_device_center_dump(void);
uint8_t ticos_device_center_ndev(void);

extern ticos_device_t* ticos_device_list[];

#define ticos_dev(id, type)    \
    ((type##_t*)(ticos_device_list[id]))

#define ticos_dev_name(id)        \
    (ticos_device_list[id]->name)

#define ticos_dev_isdirty(id, type, var)   \
    (((type##_t*) ticos_device_list[id])->_##var##_dirty)

#define ticos_dev_getval(id, type, var)  \
    (((type##_t*) ticos_device_list[id])->_##var##_var)

#define ticos_dev_setval(id, type, var, val) \
    (((type##_t*) ticos_device_list[id])->_##var##_var = val)

#ifdef __cplusplus
}
#endif

#endif // __TICOS_DEVICE_CENTER_H
