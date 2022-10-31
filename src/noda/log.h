#ifndef __NODA_LOG_H
#define __NODA_LOG_H

#include "noda/common.h"
#include <stdio.h>

#define ticos_print  printf

#define ticos_println(...) \
    do { ticos_print(__VA_ARGS__); ticos_print("\n"); } while (0)

#define ticos_log_internal(level, ...) \
    do { ticos_print(level "> "); ticos_println(__VA_ARGS__); } while (0)

#define ticos_logv(...)  ticos_log_internal("V", __VA_ARGS__)
#define ticos_logd(...)  ticos_log_internal("D", __VA_ARGS__)
#define ticos_logi(...)  ticos_log_internal("I", __VA_ARGS__)
#define ticos_logw(...)  ticos_log_internal("W", __VA_ARGS__)
#define ticos_loge(...)  ticos_log_internal("E", __VA_ARGS__)

#endif // __NODA_LOG_H
