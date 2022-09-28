#ifndef __NODA_DEVICE_CENTER_H
#define __NODA_DEVICE_CENTER_H

#include "noda_common.h"
#include "noda_device.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NODA_DEVICE_LIST  \
    static noda_device_t* noda_device_list[] =

#define NODA_DEVICE_ADD(dev, ...) \
    (noda_device_t*) &((dev##_t) { \
        NODA_DEVICE_SET_VTABLE(dev), \
        __VA_ARGS__ \
    }),

#define noda_device_center_startup() \
    noda_device_center_startup_internal(\
            sizeof(noda_device_list)/sizeof(noda_device_t*), \
            noda_device_list);

int noda_device_center_startup_internal(int ndev, noda_device_t** devs);
int noda_device_center_cleanup(void);
int noda_device_center_sync(void);
int noda_device_center_post(void);
int noda_device_center_dump(void);

#ifdef __cplusplus
}
#endif

#endif // __NODA_DEVICE_CENTER_H
