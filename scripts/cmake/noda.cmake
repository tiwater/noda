set (NODA_PLATFORM_DIR  ${NODA_PATH}/platforms/${NODA_PLATFORM})
set (NODA_LIBRARY_DIR   ${NODA_PATH}/noda-library)

aux_source_directory (${NODA_LIBRARY_DIR}/src/core  CORE_SRCS)
aux_source_directory (${NODA_PLATFORM_DIR}/src      PLATFORM_SRCS)
set (NODA_SRCS ${PLATFORM_SRCS} ${CORE_SRCS})
set (NODA_INCS ${NODA_LIBRARY_DIR}/src ${NODA_PLATFORM_DIR}/inc)
