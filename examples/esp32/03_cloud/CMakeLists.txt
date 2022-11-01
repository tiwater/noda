# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required (VERSION 3.20)

include ($ENV{IDF_PATH}/tools/cmake/project.cmake)

if (DEFINED ENV{NODA_PATH})
set (NODA_PATH $ENV{NODA_PATH})
else ()
set (NODA_PATH ${CMAKE_SOURCE_DIR}/../../..)
endif ()
set (NODA_PLATFORM esp32)
set (NODA_USE_FREERTOS TRUE)

if (DEFINED ENV{TICOS_SDK_PATH})
set (TICOS_SDK_SRC_PATH $ENV{TICOS_SDK_PATH}/src)
else ()
set (TICOS_SDK_SRC_PATH ${NODA_PATH}/../ticos-sdk-for-c/src)
endif ()
aux_source_directory (${TICOS_SDK_SRC_PATH}   TICOS_SRCS)

aux_source_directory (${CMAKE_SOURCE_DIR}/main   PROJ_SRCS)

include (${NODA_PATH}/scripts/cmake/noda.cmake)

project (03_cloud)

