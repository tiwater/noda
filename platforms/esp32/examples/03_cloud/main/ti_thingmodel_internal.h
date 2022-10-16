#ifndef __TI_THING_MODEL_INTERNAL_H
#define __TI_THING_MODEL_INTERNAL_H

typedef enum {
    TICOS_IOT_VAL_TYPE_BOOLEAN,
    TICOS_IOT_VAL_TYPE_INTEGER,
    TICOS_IOT_VAL_TYPE_FLOAT,
    TICOS_IOT_VAL_TYPE_STRING,
} ti_iot_val_type_t;

typedef struct {
    const char *id;
    ti_iot_val_type_t type;
    void *func;
} ti_iot_telemetry_info_t;

typedef struct {
    const char *id;
    ti_iot_val_type_t type;
    void *upload_func;
    void *download_func;
} ti_iot_property_info_t;

typedef struct {
    const char *id;
    ti_iot_val_type_t type;
    void *func;
} ti_iot_command_info_t;

#endif // __TI_THING_MODEL_INTERNAL_H
