#ifndef __TICOS_WIFI_H
#define __TICOS_WIFI_H

#include "ticos/common.h"

#ifdef __cplusplus
extern "C" {
#endif

void ticos_wifi_start_as_sta(const char* ssid, const char* pswd);
void ticos_wifi_stop(void);

#ifdef __cplusplus
}
#endif

#endif // __TICOS_WIFI_H
