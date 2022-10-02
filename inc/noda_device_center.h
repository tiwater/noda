#ifndef __NODA_DEVICE_CENTER_H
#define __NODA_DEVICE_CENTER_H

#include "noda_common.h"
#include "noda_device.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NODA_DEVICE_ID_MAP \
    enum noda_device_id_t

#define NODA_DEVICE_LIST  \
    noda_device_t* const noda_device_list[] =

#define NODA_DEVICE_ADD(_id, dev, ...) \
    [_id] = (noda_device_t*) &((dev##_t) { \
        NODA_DEVICE_SET_VTABLE(dev), \
        .name = #_id, \
        __VA_ARGS__ \
    }),

#define NODA_NDEV   (sizeof(noda_device_list)/sizeof(noda_device_t*))

#define noda_getval(id, devtype, var)  \
    (((devtype##_t*) noda_device_list[id])->_##var##_var)

#define noda_setval(id, devtype, var, val) \
    (((devtype##_t*) noda_device_list[id])->_##var##_var = val)

#define noda_device_center_startup() \
    noda_device_center_startup_internal(NODA_NDEV)
int noda_device_center_startup_internal(uint8_t ndev);
int noda_device_center_cleanup(void);
int noda_device_center_sync(void);
int noda_device_center_post(void);
int noda_device_center_dump(void);

extern noda_device_t* const noda_device_list[];

#ifdef __cplusplus
}
#endif

#endif // __NODA_DEVICE_CENTER_H
