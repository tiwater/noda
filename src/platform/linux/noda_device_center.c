#include "noda_device_center.h"
#include "noda_utils.h"
#include "noda_log.h"

#include <pthread.h>
#include <string.h>

typedef struct {
    pthread_t tid;
    volatile bool running;
} task_t;

static task_t s_task;
static noda_device_t** s_devs;
static int s_ndev;

static void* _runner(void* args) {
    task_t* task = (task_t*) args;
    noda_device_t** devs = s_devs;
    int ndev = s_ndev;
    task->running = true;
    noda_device_t* dev;
    for (int i = 0; i < ndev; ++i) {
        dev = devs[i];
        if (!dev->opened) {
            if (dev->open && NODA_OK == dev->open(dev)) {
                noda_logd("device %d:%s open", i, dev->name);
                dev->opened = true;
            } else {
                noda_loge("fail to open device %d:%s", i, dev->name);
            }
        }
    }
    while (task->running) {
        // TODO
        noda_throttle(1000);
    }
    for (int i = 0; i < ndev; ++i) {
        dev = devs[i];
        if (dev->opened) {
            if (dev->close && NODA_OK == dev->close(dev)) {
                noda_logd("device %d:%s close", i, dev->name);
                dev->opened = false;
            } else {
                noda_loge("fail to close device %d:%s", i, dev->name);
            }
        }
    }
    return NULL;
}

int noda_device_center_startup_internal(int ndev, noda_device_t** devs) {
    if (!s_task.running && ndev > 0 && devs) {
        s_devs = devs;
        s_ndev = ndev;
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
        s_devs = NULL;
        s_ndev = 0;
        memset(&s_task, 0, sizeof(s_task));
        noda_logd("device center cleanup");
        return NODA_OK;
    }
    return NODA_FAIL;
}

int noda_device_center_sync(void) {
    if (!s_task.running) {
        return NODA_FAIL;
    }
    noda_device_t** devs = s_devs;
    int ndev = s_ndev;
    noda_device_t* dev;
    for (int i = 0; i < ndev; ++i) {
        dev = devs[i];
        if (dev->opened) {
            if (dev->copy_cache && NODA_OK == dev->copy_cache(dev)) {
                noda_logd("device %d:%s sync", i, dev->name);
            }
        }
    }
    return NODA_OK;
}

int noda_device_center_post(void) {
    if (!s_task.running) {
        return NODA_FAIL;
    }
    noda_device_t** devs = s_devs;
    int ndev = s_ndev;
    noda_device_t* dev;
    for (int i = 0; i < ndev; ++i) {
        dev = devs[i];
        if (dev->opened) {
            if (dev->post_cache && NODA_OK == dev->post_cache(dev)) {
                noda_logd("device %d:%s post", i, dev->name);
            }
        }
    }
    return NODA_OK;
}

noda_device_t* noda_device_center_search(const char* devname) {
    noda_device_t** devs = s_devs;
    noda_device_t* dev;
    // TODO 将搜索时间控制在O(1)
    for (int i = 0, ndev = s_ndev; i < ndev; ++i) {
        dev = devs[i];
        if (0 == strcmp(dev->name, devname)) {
            return dev;
        }
    }
    noda_loge("device %s not found", devname);
    return NULL;
}
