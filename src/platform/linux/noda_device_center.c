#include "noda_device_center.h"
#include "noda_utils.h"
#include "noda_log.h"

#include <pthread.h>
#include <string.h>

typedef struct {
    pthread_t tid;
    pthread_mutex_t lock;
    volatile bool running;
} task_t;

static task_t s_task;
static uint8_t s_ndev;

static int noda_device_center_sync_cache_from_dev(void) {
    noda_device_t* const* devs = noda_device_list;
    noda_device_t* dev;
    for (int i = 0, n = s_ndev; i < n; ++i) {
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
    for (int i = 0, n = s_ndev; i < n; ++i) {
        dev = devs[i];
        if (dev->opened) {
            dev->post_cache_to_dev(dev);
        }
    }
    return NODA_OK;
}

static void* _runner(void* args) {
    task_t* task = (task_t*) args;
    noda_device_t* const* devs = noda_device_list;
    task->running = true;
    noda_device_t* dev;
    for (int i = 0, n = s_ndev; i < n; ++i) {
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
    while (task->running) {
        noda_device_center_post_cache_to_dev();
        noda_throttle(200);
        noda_device_center_sync_cache_from_dev();
    }
    for (int i = 0, n = s_ndev; i < n; ++i) {
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

int noda_device_center_startup_internal(uint8_t ndev) {
    if (!s_task.running && ndev > 0) {
        s_ndev = ndev;
        pthread_mutex_init(&s_task.lock, NULL);
        if (0 == pthread_create(&s_task.tid, NULL, _runner, (void*)&s_task)) {
            noda_logd("device center startup");
            return NODA_OK;
        }
        noda_loge("fail to create device center task");
    }
    return NODA_FAIL;
}

int noda_device_center_cleanup(void) {
    if (s_task.running) {
        s_task.running = false;
        pthread_join(s_task.tid, NULL);
        pthread_mutex_destroy(&s_task.lock);
        s_ndev = 0;
        memset(&s_task, 0, sizeof(s_task));
        noda_logd("device center cleanup");
        return NODA_OK;
    }
    return NODA_FAIL;
}

int noda_device_center_sync(void) {
    noda_device_t* const* devs = noda_device_list;
    noda_device_t* dev;
    for (int i = 0, n = s_ndev; i < n; ++i) {
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
    for (int i = 0, n = s_ndev; i < n; ++i) {
        dev = devs[i];
        if (dev->opened) {
            dev->post_to_cache(dev);
        }
    }
    return NODA_OK;
}
