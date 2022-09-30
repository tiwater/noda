
#include "noda_arduino_device_center.h"
#include "noda_utils.h"
#include "noda_log.h"
#include "noda.h"
//#include "SCoop.h" //THREAD SUPPORTED BY ARDUINO

#if platform==1
#include <string.h>
/*
typedef struct {
    pthread_t tid;
    noda_device_t** devs;
    int ndev;
    volatile bool running;
} task_t;
*/
/*
static task_t s_task;
*/
static void* _runner(void* args) {
    //return NULL;
}

int noda_arduino_device_center_startup_internal(int ndev, noda_device_t** devs) {
    return NODA_FAIL;
}

int noda_arduino_device_center_cleanup(void) {
    return NODA_FAIL;
}

int noda_arduino_device_center_sync(void) {
    return NODA_OK;
}

int noda_arduino_device_center_post(void) {
    return NODA_OK;
}

int noda_arduino_device_center_dump(void) {
    return NODA_OK;
}
#endif