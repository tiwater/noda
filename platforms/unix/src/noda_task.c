#include "noda_task.h"

#include <pthread.h>
#include <stdlib.h>
#include "noda_log.h"

typedef struct {
    noda_task_runner_t runner;
    volatile bool running;
    pthread_t tid;
} internal_task_t;

static void* _runner(void* task) {
    noda_task_t* _task = (noda_task_t*) task;
    if (_task && _task->runner) {
        _task->running = true;
        return _task->runner(_task);
    }
    return NULL;
}

noda_task_t* noda_task_create(const char* name, noda_task_runner_t runner) {
    NODA_UNUSED(name);
    internal_task_t* task = calloc(1, sizeof(internal_task_t));
    if (task) {
        task->runner = runner;
        if (0 != pthread_create(&task->tid, NULL, _runner, (void*)task)) {
            noda_loge("node_task_create: fail to create task!");
            free(task);
            task = NULL;
        }
    } else {
        noda_loge("noda_task_create: memory leak!");
    }
    return (noda_task_t*) task;
}

void noda_task_destroy(noda_task_t* task) {
    internal_task_t* _task = (internal_task_t*) task;
    if (_task) {
        _task->running = false;
        pthread_join(_task->tid, NULL);
        free(_task);
    }
}
