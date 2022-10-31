#include "noda/time.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void ticos_delay(clock_t ms) {
    vTaskDelay(ms / portTICK_PERIOD_MS);
}
