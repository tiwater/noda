# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required (VERSION 3.20)

include ($ENV{IDF_PATH}/tools/cmake/project.cmake)

if (NOT DEFINED ENV{NODA_PATH})
set (NODA_PATH ${CMAKE_SOURCE_DIR}/../../../..)
endif ()
set (NODA_PLATFORM_DIR ${NODA_PATH}/platforms/esp32)

aux_source_directory (${NODA_PATH}/core                 CORE_SRCS)
aux_source_directory (${NODA_PLATFORM_DIR}/src          PLATFORM_SRCS)
set (NODA_SRCS ${PLATFORM_SRCS} ${CORE_SRCS})

set (NODA_INCS ${NODA_PATH}/inc ${NODA_PLATFORM_DIR}/inc)

project (01_device)

