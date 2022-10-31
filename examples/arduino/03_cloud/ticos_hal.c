#include <ticos_api.h>
#include <mqtt_client.h>

static esp_mqtt_client_handle_t mqtt_client;

/**
 * @brief mqtt客户端向云端推送数据的接口
 * @note  ticos sdk会调用此接口，完成数据的上传。需要用户实现此函数
 * @param topic 上报信息的topic
 * @param data 上报的数据内容
 * @param len  上报的数据长度
 * @param qos  通信质量
 * @param retain retain flag
 * @return 0 for success, other for fail.
 */
int ticos_hal_mqtt_publish(const char *topic, const char *data, int len, int qos, int retain) {
    return esp_mqtt_client_publish(mqtt_client, topic, data, len, qos, retain);
}

/**
 * @brief mqtt客户端订阅云端topic接口
 * @note  ticos sdk会调用此接口，完成指定topic的订阅。需要用户实现此函数
 * @param topic 需要订阅的topic
 * @param qos  通信质量
 * @return 0 for success, other for fail.
 */
int ticos_hal_mqtt_subscribe(const char *topic, int qos) {
    return esp_mqtt_client_subscribe(mqtt_client, topic, qos);
}

/**
 * @brief 平台相关mqtt事件回调接口
 * @note  当使用mqtt client连接云端成功后，会产生MQTT_EVENT_CONNECTED事件，
 * 此时用户需要调用ticos_mqtt_subscribe()订阅和云端通信相关的topic
 * 当client从云端接收到数据后，会产生MQTT_EVENT_DATA事件，
 * 此时用户需要回调ticos_msg_recv()将数据传给sdk进行处理
 */
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event) {
#else
static void mqtt_event_handler(void *args, esp_event_base_t base, int32_t id, void *data) {
#endif
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
    int32_t id = event->event_id;
#else
    esp_mqtt_event_handle_t event = data;
#endif
    switch (id) {
        case MQTT_EVENT_CONNECTED:
            printf("MQTT event MQTT_EVENT_CONNECTED");
            ticos_mqtt_subscribe();
            break;
        case MQTT_EVENT_DATA:
            printf("MQTT event MQTT_EVENT_DATA");
            ticos_msg_recv(event->topic, event->data, event->data_len);
            break;
        default:
            printf("mqtt event: id = %d\n", event->event_id);
            break;
    }
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
    return ESP_OK;
#endif
}

/**
 * @brief 启动平台相关的mqtt服务
 * @note  用户需要根据平台实现此函数，提供一个mqtt的客户端。ticos sdk会调用此接口连接到云端
 */
int ticos_hal_mqtt_start(const char* mqtt_uri,
                         int         mqtt_port,
                         const char* mqtt_client_id,
                         const char* mqtt_user_name,
                         const char *passwd) {
    esp_mqtt_client_config_t mqtt_config = {
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
        .uri        = mqtt_uri,
        .port       = mqtt_port,
        .client_id  = mqtt_client_id,
        .username   = mqtt_user_name,
        .password = passwd,
        .keepalive = 30,
        .event_handle = mqtt_event_handler,
#else
        .broker.address.uri     = mqtt_uri,
        .broker.address.port    = mqtt_port,
        .credentials.client_id  = mqtt_client_id,
        .credentials.username   = mqtt_user_name,
        .session.keepalive = 30,
#endif
    };

    mqtt_client = esp_mqtt_client_init(&mqtt_config);

    if (mqtt_client == NULL) {
        printf("Failed creating mqtt client");
        return 1;
    }

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
    esp_mqtt_client_register_event(mqtt_client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
#endif

    if (ESP_OK != esp_mqtt_client_start(mqtt_client)) {
        printf("Could not start mqtt client; error code:");
        return 1;
    }
    printf("MQTT client started");
    return 0;
}

/**
 * @brief 停止平台相关的mqtt服务
 * @note  该函数停止mqtt客户端与云端的连接, 需要用户根据平台实现。ticos sdk停止时会调用此接口
 */
void ticos_hal_mqtt_stop() {
    esp_mqtt_client_stop(mqtt_client);
    mqtt_client = NULL;
}
