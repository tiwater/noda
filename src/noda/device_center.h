#ifndef __NODA_DEVICE_CENTER_H
#define __NODA_DEVICE_CENTER_H

#include "noda/common.h"
#include "noda/device.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NODA_DEV_ID_BEGIN \
    enum noda_device_id_t {

#define NODA_DEV_ID_END \
    NODA_NDEV, \
    };

#define NODA_DEV_ADD(_id, dev, ...) \
    do { \
        static dev##_t dev##_id = { \
            NODA_DEV_SET_VTABLE(dev), .name = #_id, __VA_ARGS__ \
        }; \
        noda_device_list[_id] = (noda_device_t*)&dev##_id; \
    } while (0)

int noda_device_center_startup(void);
int noda_device_center_cleanup(void);
int noda_device_center_sync(void);
int noda_device_center_post(void);
int noda_device_center_dump(void);
uint8_t noda_device_center_ndev(void);

extern noda_device_t* noda_device_list[];

#define noda_dev(id, type)    \
    ((type##_t*)(noda_device_list[id]))

#define noda_dev_name(id)        \
    (noda_device_list[id]->name)

#define noda_dev_isdirty(id, type, var)   \
    (((type##_t*) noda_device_list[id])->_##var##_dirty)

#define noda_dev_getval(id, type, var)  \
    (((type##_t*) noda_device_list[id])->_##var##_var)

#define noda_dev_setval(id, type, var, val) \
    (((type##_t*) noda_device_list[id])->_##var##_var = val)

#ifdef __cplusplus
}
#endif

#endif // __NODA_DEVICE_CENTER_H
