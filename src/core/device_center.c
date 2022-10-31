#include "noda/device_center.h"
#include "noda/task.h"
#include "noda/time.h"
#include "noda/log.h"

static ticos_task_t* s_task;

static int ticos_device_center_sync_cache_from_dev(void) {
    ticos_device_t* const* devs = ticos_device_list;
    ticos_device_t* dev;
    for (int i = 0, n = ticos_device_center_ndev(); i < n; ++i) {
        dev = devs[i];
        if (dev->opened) {
            dev->sync_cache_from_dev(dev);
        }
    }
    return NODA_OK;
}

static int ticos_device_center_post_cache_to_dev(void) {
    ticos_device_t* const* devs = ticos_device_list;
    ticos_device_t* dev;
    for (int i = 0, n = ticos_device_center_ndev(); i < n; ++i) {
        dev = devs[i];
        if (dev->opened) {
            dev->post_cache_to_dev(dev);
        }
    }
    return NODA_OK;
}

static void* _runner(ticos_task_t* task) {
    ticos_device_t* const* devs = ticos_device_list;
    ticos_device_t* dev;
    for (int i = 0, n = ticos_device_center_ndev(); i < n; ++i) {
        dev = devs[i];
        if (!dev->opened) {
            if (NODA_OK == dev->open(dev)) {
                ticos_logd("device %d:%s open", i, dev->name);
                dev->opened = true;
            } else {
                ticos_loge("fail to open device %d:%s", i, dev->name);
            }
        }
    }
    while (ticos_task_running(task)) {
        ticos_device_center_post_cache_to_dev();
        ticos_delay(20);
        ticos_device_center_sync_cache_from_dev();
    }
    for (int i = 0, n = ticos_device_center_ndev(); i < n; ++i) {
        dev = devs[i];
        if (dev->opened) {
            if (NODA_OK == dev->close(dev)) {
                ticos_logd("device %d:%s close", i, dev->name);
                dev->opened = false;
            } else {
                ticos_loge("fail to close device %d:%s", i, dev->name);
            }
        }
    }
    return NULL;
}

int ticos_device_center_startup(void) {
    uint8_t ndev = ticos_device_center_ndev();
    if (ndev > 0) {
        if (!s_task) {
            s_task = ticos_task_create("ticos_device_center", _runner);
        }
        if (s_task) {
            ticos_logd("device center startup");
            return NODA_OK;
        }
        ticos_loge("fail to startup device center!");
        return NODA_FAIL;
    }
    return NODA_OK;
}

int ticos_device_center_cleanup(void) {
    if (s_task) {
        ticos_task_destroy(s_task);
        s_task = NULL;
        ticos_logd("device center cleanup");
    }
    return NODA_OK;
}

int ticos_device_center_sync(void) {
    ticos_device_t* const* devs = ticos_device_list;
    ticos_device_t* dev;
    for (int i = 0, n = ticos_device_center_ndev(); i < n; ++i) {
        dev = devs[i];
        if (dev->opened) {
            dev->sync_from_cache(dev);
        }
    }
    return NODA_OK;
}

int ticos_device_center_post(void) {
    ticos_device_t* const* devs = ticos_device_list;
    ticos_device_t* dev;
    for (int i = 0, n = ticos_device_center_ndev(); i < n; ++i) {
        dev = devs[i];
        if (dev->opened) {
            dev->post_to_cache(dev);
        }
    }
    return NODA_OK;
}
