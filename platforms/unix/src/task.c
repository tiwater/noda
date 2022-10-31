#include "ticos/task.h"

#include <pthread.h>
#include <stdlib.h>

#include "ticos/log.h"

typedef struct {
    ticos_task_runner_t runner;
    volatile bool running;
    pthread_t tid;
} internal_task_t;

static void* _runner(void* task) {
    ticos_task_t* _task = (ticos_task_t*) task;
    if (_task && _task->runner) {
        _task->running = true;
        return _task->runner(_task);
    }
    return NULL;
}

ticos_task_t* ticos_task_create(const char* name, ticos_task_runner_t runner) {
    TICOS_UNUSED(name);
    internal_task_t* task = calloc(1, sizeof(internal_task_t));
    if (task) {
        task->runner = runner;
        if (0 != pthread_create(&task->tid, NULL, _runner, (void*)task)) {
            ticos_loge("node_task_create: fail to create task!");
            free(task);
            task = NULL;
        }
    } else {
        ticos_loge("ticos_task_create: memory leak!");
    }
    return (ticos_task_t*) task;
}

void ticos_task_destroy(ticos_task_t* task) {
    internal_task_t* _task = (internal_task_t*) task;
    if (_task) {
        _task->running = false;
        pthread_join(_task->tid, NULL);
        free(_task);
    }
}
