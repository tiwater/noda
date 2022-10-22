#include "noda/time.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void noda_delay(clock_t ms) {
    vTaskDelay(ms / portTICK_PERIOD_MS);
}
