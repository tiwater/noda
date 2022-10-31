#ifndef __NODA_WIFI_H
#define __NODA_WIFI_H

#include "noda/common.h"

#ifdef __cplusplus
extern "C" {
#endif

void ticos_wifi_start_as_sta(const char* ssid, const char* pswd);
void ticos_wifi_stop(void);

#ifdef __cplusplus
}
#endif

#endif // __NODA_WIFI_H
