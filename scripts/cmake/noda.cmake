set (NODA_PLATFORM_DIR ${NODA_PATH}/platforms/esp32)

aux_source_directory (${NODA_PATH}/core                 CORE_SRCS)
aux_source_directory (${NODA_PLATFORM_DIR}/src          PLATFORM_SRCS)
set (NODA_SRCS ${PLATFORM_SRCS} ${CORE_SRCS})
set (NODA_INCS ${NODA_PATH}/inc ${NODA_PLATFORM_DIR}/inc)
