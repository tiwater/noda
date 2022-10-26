#ifndef __NODA_MQTT_H
#define __NODA_MQTT_H

#include "noda/common.h"

#ifdef __cplusplus
extern "C" {
#endif

int noda_mqtt_start(const char* fqdn,
                    const char* product_id,
                    const char* device_id);

int noda_mqtt_stop(void);

#ifdef __cplusplus
}
#endif

#endif // __NODA_MQTT_H
