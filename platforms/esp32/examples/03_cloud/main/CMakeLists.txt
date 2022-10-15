idf_component_register (
        SRCS
        ${NODA_SRCS}
        ${NODA_PATH}/examples/03_cloud/main.c
        noda_iot.c
        ti_thingmodel.c
        INCLUDE_DIRS
        ${NODA_INCS}
        .)
