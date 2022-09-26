#ifndef __NODA_LOG_H
#define __NODA_LOG_H

#include <stdio.h>

#define noda_print  printf

#define noda_println(...) \
    do { noda_print(__VA_ARGS__); noda_print("\n"); } while (0)

#define noda_log_internal(level, ...) \
    do { noda_print(level "> "); noda_println(__VA_ARGS__); } while (0)

#define noda_logv(...)  noda_log_internal("V", __VA_ARGS__)
#define noda_logd(...)  noda_log_internal("D", __VA_ARGS__)
#define noda_logi(...)  noda_log_internal("I", __VA_ARGS__)
#define noda_logw(...)  noda_log_internal("W", __VA_ARGS__)
#define noda_loge(...)  noda_log_internal("E", __VA_ARGS__)

#endif // __NODA_LOG_H
