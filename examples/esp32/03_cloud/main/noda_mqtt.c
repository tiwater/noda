#include "noda_mqtt.h"
#include <stdlib.h>
#include <string.h>
#include <mqtt_client.h>
#include <noda/log.h>

static esp_mqtt_client_handle_t mqtt_client;
static char property_topic[128];
static noda_mqtt_client_on_recv_cb s_noda_mqtt_client_on_recv_cb;

bool noda_mqtt_client_publish(const char* topic, const char* data, size_t len) {
    return ESP_OK == esp_mqtt_client_publish(mqtt_client, topic, data, len, 1, 0);
}

void noda_mqtt_client_set_on_recv_cb(noda_mqtt_client_on_recv_cb cb) {
    s_noda_mqtt_client_on_recv_cb = cb;
}

/**
 * @brief 平台相关mqtt事件回调接口
 * @note  当使用mqtt client连接云端成功后，会产生MQTT_EVENT_CONNECTED事件；
 *        当client从云端接收到数据后，会产生MQTT_EVENT_DATA事件
 */
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event) {
#else
static void mqtt_event_handler(void *args, esp_event_base_t base, int32_t id, void *data) {
#endif
    int r;
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
    int32_t id = event->event_id;
#else
    esp_mqtt_event_handle_t event = data;
#endif
    switch (id) {
        case MQTT_EVENT_ERROR:
            noda_logd("MQTT event MQTT_EVENT_ERROR");
            break;
        case MQTT_EVENT_CONNECTED:
            noda_logd("MQTT event MQTT_EVENT_CONNECTED");
            r = esp_mqtt_client_subscribe(mqtt_client, property_topic, 1);
            if (r == -1) {
                noda_loge("Could not subscribe for cloud-to-device messages.");
            } else {
                noda_logd("Subscribed for cloud-to-device messages.");
            }
            break;
        case MQTT_EVENT_DISCONNECTED:
            noda_logd("MQTT event MQTT_EVENT_DISCONNECTED");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            noda_logd("MQTT event MQTT_EVENT_SUBSCRIBED");
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            noda_logd("MQTT event MQTT_EVENT_UNSUBSCRIBED");
            break;
        case MQTT_EVENT_PUBLISHED:
            noda_logd("MQTT event MQTT_EVENT_PUBLISHED");
            break;
        case MQTT_EVENT_DATA:
            noda_logd("MQTT event MQTT_EVENT_DATA");
            if (s_noda_mqtt_client_on_recv_cb) {
                s_noda_mqtt_client_on_recv_cb(event->data, event->data_len);
            }
            break;
        case MQTT_EVENT_BEFORE_CONNECT:
            noda_logd("MQTT event MQTT_EVENT_BEFORE_CONNECT");
            break;
        default:
            noda_loge("MQTT event UNKNOWN");
            break;
    }
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
    return ESP_OK;
#endif
}

int noda_mqtt_client_start(const char* mqtt_fqdn,
                           const char* mqtt_client_id,
                           const char* mqtt_username,
                           const char* device_id) {
    snprintf(property_topic, sizeof(property_topic),
            "devices/%s/twin/patch/desired", device_id);

    char hub_uri[128] = {};
    snprintf(hub_uri, sizeof(hub_uri), "mqtt://%s", mqtt_fqdn);
    esp_mqtt_client_config_t mqtt_config = {
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
        .uri = hub_uri,
        .port = 1883,
        .client_id = mqtt_client_id,
        .username = mqtt_username,
        .keepalive = 30,
        .disable_clean_session = false,
        .disable_auto_reconnect = false,
        .event_handle = mqtt_event_handler,
#else
        .broker.address.uri = hub_uri,
        .broker.address.port = 1883,
        .credentials.client_id = mqtt_client_id,
        .credentials.username = mqtt_username,
        .session.keepalive = 30,
        .session.disable_clean_session = false,
        .network.disable_auto_reconnect = false,
#endif
    };

    mqtt_client = esp_mqtt_client_init(&mqtt_config);

    if (mqtt_client == NULL) {
        noda_loge("Failed creating mqtt client");
        return NODA_FAIL;
    }

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
    esp_mqtt_client_register_event(mqtt_client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
#endif

    esp_err_t start_result = esp_mqtt_client_start(mqtt_client);

    if (start_result != ESP_OK) {
        noda_loge("Could not start mqtt client; error code:");
        return NODA_FAIL;
    }

    noda_logd("MQTT client started");
    return NODA_OK;
}

int noda_mqtt_client_stop(void)
{
    esp_mqtt_client_stop(mqtt_client);
    mqtt_client = NULL;
    return NODA_OK;
}
