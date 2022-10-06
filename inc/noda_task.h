#ifndef __NODA_TASK_H
#define __NODA_TASK_H

#include "noda_common.h"

#ifdef __cplusplus
extern "C" {
#endif

struct noda_task_t;
typedef struct noda_task_t noda_task_t;

typedef void* (*noda_task_runner_t) (struct noda_task_t* task);

struct noda_task_t {
    noda_task_runner_t runner;
    volatile bool running;
};

noda_task_t* noda_task_create(const char* name, noda_task_runner_t runner);
void noda_task_destroy(noda_task_t* task);
#define noda_task_running(task)     ((task) ? (task)->running : false)

#ifdef __cplusplus
}
#endif

#endif // __NODA_TASK_H
