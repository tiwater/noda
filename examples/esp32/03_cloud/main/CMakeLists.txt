idf_component_register (
        SRCS
        ${NODA_SRCS}
        ${TI_IOT_SRCS}
        main.c
        noda_iot.c
        noda_wifi.c
        ti_iot_hal.c
        ti_thingmodel.c
        INCLUDE_DIRS
        ${NODA_INCS}
        ${TI_IOT_SRC_DIR}
        .)
