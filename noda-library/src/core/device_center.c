#include "noda/device_center.h"
#include "noda/task.h"
#include "noda/time.h"
#include "noda/log.h"

static noda_task_t* s_task;

static int noda_device_center_sync_cache_from_dev(void) {
    noda_device_t* const* devs = noda_device_list;
    noda_device_t* dev;
    for (int i = 0, n = noda_device_center_ndev(); i < n; ++i) {
        dev = devs[i];
        if (dev->opened) {
            dev->sync_cache_from_dev(dev);
        }
    }
    return NODA_OK;
}

static int noda_device_center_post_cache_to_dev(void) {
    noda_device_t* const* devs = noda_device_list;
    noda_device_t* dev;
    for (int i = 0, n = noda_device_center_ndev(); i < n; ++i) {
        dev = devs[i];
        if (dev->opened) {
            dev->post_cache_to_dev(dev);
        }
    }
    return NODA_OK;
}

static void* _runner(noda_task_t* task) {
    noda_device_t* const* devs = noda_device_list;
    noda_device_t* dev;
    for (int i = 0, n = noda_device_center_ndev(); i < n; ++i) {
        dev = devs[i];
        if (!dev->opened) {
            if (NODA_OK == dev->open(dev)) {
                noda_logd("device %d:%s open", i, dev->name);
                dev->opened = true;
            } else {
                noda_loge("fail to open device %d:%s", i, dev->name);
            }
        }
    }
    while (noda_task_running(task)) {
        noda_device_center_post_cache_to_dev();
        noda_delay(200);
        noda_device_center_sync_cache_from_dev();
    }
    for (int i = 0, n = noda_device_center_ndev(); i < n; ++i) {
        dev = devs[i];
        if (dev->opened) {
            if (NODA_OK == dev->close(dev)) {
                noda_logd("device %d:%s close", i, dev->name);
                dev->opened = false;
            } else {
                noda_loge("fail to close device %d:%s", i, dev->name);
            }
        }
    }
    return NULL;
}

int noda_device_center_startup(void) {
    uint8_t ndev = noda_device_center_ndev();
    if (ndev > 0) {
        if (!s_task) {
            s_task = noda_task_create("noda_device_center", _runner);
        }
        if (s_task) {
            noda_logd("device center startup");
            return NODA_OK;
        }
        noda_loge("fail to startup device center!");
        return NODA_FAIL;
    }
    return NODA_OK;
}

int noda_device_center_cleanup(void) {
    if (s_task) {
        noda_task_destroy(s_task);
        s_task = NULL;
        noda_logd("device center cleanup");
    }
    return NODA_OK;
}

int noda_device_center_sync(void) {
    noda_device_t* const* devs = noda_device_list;
    noda_device_t* dev;
    for (int i = 0, n = noda_device_center_ndev(); i < n; ++i) {
        dev = devs[i];
        if (dev->opened) {
            dev->sync_from_cache(dev);
        }
    }
    return NODA_OK;
}

int noda_device_center_post(void) {
    noda_device_t* const* devs = noda_device_list;
    noda_device_t* dev;
    for (int i = 0, n = noda_device_center_ndev(); i < n; ++i) {
        dev = devs[i];
        if (dev->opened) {
            dev->post_to_cache(dev);
        }
    }
    return NODA_OK;
}
