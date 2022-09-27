#include "noda_device_center.h"
#include "noda_utils.h"
#include "noda_log.h"

#include <pthread.h>
#include <string.h>

typedef struct {
    pthread_t tid;
    noda_device_t** devs;
    int ndev;
    volatile bool running;
} task_t;

static task_t s_task;

static void* _runner(void* args) {
    task_t* task = (task_t*) args;
    noda_device_t** devs = task->devs;
    int ndev = task->ndev;
    task->running = true;
    noda_device_t* dev;
    for (int i = 0; i < ndev; ++i) {
        dev = devs[i];
        if (dev->open && NODA_OK == dev->open(dev)) {
            noda_logd("open device %d:%s", i, dev->name);
        } else {
            noda_loge("fail to open device %d:%s", i, dev->name);
        }
    }
    while (task->running) {
        noda_throttle(1000);
    }
    for (int i = 0; i < ndev; ++i) {
        dev = devs[i];
        if (dev->close && NODA_OK == dev->close(dev)) {
            noda_logd("close device %d:%s", i, dev->name);
        } else {
            noda_loge("fail to close device %d:%s", i, dev->name);
        }
    }
    return NULL;
}

int noda_device_center_startup_internal(int ndev, noda_device_t** devs) {
    if (!s_task.running && ndev > 0 && devs) {
        if (0 == pthread_create(&s_task.tid, NULL, _runner, (void*)&s_task)) {
            s_task.devs = devs;
            s_task.ndev = ndev;
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
        memset(&s_task, 0, sizeof(s_task));
        noda_logd("device center cleanup");
        return NODA_OK;
    }
    return NODA_FAIL;
}

int noda_device_center_dump(void) {
    if (!s_task.running) {
        return NODA_FAIL;
    }
    noda_device_t** devs = s_task.devs;
    for (int i = 0, ndev = s_task.ndev; i < ndev; ++i) {
        noda_logd("device %d:%s dump", i, devs[i]->name);
    }
    return NODA_OK;
}
