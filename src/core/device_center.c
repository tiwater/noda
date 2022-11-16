#include "ticos/device_center.h"
#include "ticos/task.h"
#include "ticos/time.h"
#include "ticos/log.h"

extern ticos_device_t* ticos_device_list[];

#define _has_device() \
    (ticos_device_list[0])

#define _foreach_device(dev) \
    for (ticos_device_t **l = ticos_device_list, *dev = l[0]; dev; dev = *(l += 1))

static ticos_task_t* s_task;

static int _sync_from_dev(void) {
    _foreach_device(dev) {
        if (dev->opened) {
            dev->sync_from_dev(dev);
        }
    }
    return TICOS_OK;
}

static int _post_to_dev(void) {
    _foreach_device(dev) {
        if (dev->opened) {
            dev->post_to_dev(dev);
        }
    }
    return TICOS_OK;
}

static void _open(void) {
    _foreach_device(dev) {
        if (!dev->opened) {
            if (TICOS_OK == dev->open(dev)) {
                ticos_logd("device %s open", dev->name);
                dev->opened = true;
            } else {
                ticos_loge("fail to open device %s", dev->name);
            }
        }
    }
}

static void _close(void) {
    _foreach_device(dev) {
        if (dev->opened) {
            if (TICOS_OK == dev->close(dev)) {
                ticos_logd("device %s close", dev->name);
                dev->opened = false;
            } else {
                ticos_loge("fail to close device %s", dev->name);
            }
        }
    }
}

static void* _runner(ticos_task_t* task) {
    _open();
    while (ticos_task_running(task)) {
        _post_to_dev();
        ticos_delay(20);
        _sync_from_dev();
    }
    _close();
    return NULL;
}

int ticos_device_center_startup(void) {
    if (_has_device()) {
        if (!s_task) {
            s_task = ticos_task_create("ticos_device_center", _runner);
        }
        if (s_task) {
            ticos_logd("device center startup");
            return TICOS_OK;
        }
        ticos_loge("fail to startup device center!");
        return TICOS_FAIL;
    }
    return TICOS_OK;
}

int ticos_device_center_cleanup(void) {
    if (s_task) {
        ticos_task_destroy(s_task);
        s_task = NULL;
        ticos_logd("device center cleanup");
    }
    return TICOS_OK;
}

int ticos_device_center_sync(void) {
    _foreach_device(dev) {
        if (dev->opened) {
            dev->sync_from_cache(dev);
        }
    }
    return TICOS_OK;
}

int ticos_device_center_post(void) {
    _foreach_device(dev) {
        if (dev->opened) {
            dev->post_to_cache(dev);
        }
    }
    return TICOS_OK;
}
