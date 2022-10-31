#ifndef __NODA_TASK_H
#define __NODA_TASK_H

#include "noda/common.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ticos_task_t;
typedef struct ticos_task_t ticos_task_t;

typedef void* (*ticos_task_runner_t) (struct ticos_task_t* task);

struct ticos_task_t {
    ticos_task_runner_t runner;
    volatile bool running;
};

ticos_task_t* ticos_task_create(const char* name, ticos_task_runner_t runner);
void ticos_task_destroy(ticos_task_t* task);
#define ticos_task_running(task)     ((task) ? (task)->running : false)

#ifdef __cplusplus
}
#endif

#endif // __NODA_TASK_H
