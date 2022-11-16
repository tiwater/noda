#ifndef __TICOS_DEVICE_CENTER_INTERNAL_H
#define __TICOS_DEVICE_CENTER_INTERNAL_H

#undef TICOS_DEV_BEGIN
#undef TICOS_DEV_END
#undef TICOS_DEV

#define TICOS_DEV_BEGIN \
    ticos_device_t* ticos_device_list[] = {

#define TICOS_DEV_END \
        NULL, \
    };

#define TICOS_DEV(id, type, ...) \
        (ticos_device_t *) &id,

#endif // __TICOS_DEVICE_CENTER_INTERNAL_H
