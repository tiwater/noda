#include "noda/task.h"
#include "noda/log.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

typedef struct {
    ticos_task_runner_t runner;
    volatile bool running;
    TaskHandle_t tid;
} internal_task_t;


static void _runner(void* task) {
    ticos_task_t* _task = (ticos_task_t*) task;
    if (_task && _task->runner) {
        _task->running = true;
        _task->runner(_task);
   }
}

ticos_task_t* ticos_task_create(const char* name, ticos_task_runner_t runner) {
    internal_task_t* task = calloc(1, sizeof(internal_task_t));
    if (task) {
        task->runner = runner;
        // FIXME 需要完善Task配置信息
        if (pdPASS != xTaskCreate(_runner, name, 4*1024, task, 5, &task->tid)) {
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
        vTaskDelete(_task->tid);
        free(_task);
    }
}
