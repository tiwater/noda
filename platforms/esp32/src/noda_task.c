#include "noda_task.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "noda_log.h"

typedef struct {
    noda_task_runner_t runner;
    volatile bool running;
    TaskHandle_t tid;
} internal_task_t;


static void _runner(void* task) {
    noda_task_t* _task = (noda_task_t*) task;
    if (_task && _task->runner) {
        _task->running = true;
        _task->runner(_task);
   }
}

noda_task_t* noda_task_create(const char* name, noda_task_runner_t runner) {
    internal_task_t* task = calloc(1, sizeof(internal_task_t));
    if (task) {
        task->runner = runner;
        // FIXME 需要完善Task配置信息
        if (pdPASS != xTaskCreate(_runner, name, 4*1024, NULL, 5, &task->tid)) {
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
        vTaskDelete(_task->tid);
        free(_task);
    }
}
