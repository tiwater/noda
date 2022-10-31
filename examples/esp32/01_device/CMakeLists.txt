# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required (VERSION 3.20)

include ($ENV{IDF_PATH}/tools/cmake/project.cmake)

if (DEFINED ENV{TICOS_PATH})
set (TICOS_PATH $ENV{TICOS_PATH})
else ()
set (TICOS_PATH ${CMAKE_SOURCE_DIR}/../../..)
endif ()
set (TICOS_PLATFORM esp32)
set (TICOS_USE_FREERTOS TRUE)

aux_source_directory (${CMAKE_SOURCE_DIR}/main   PROJ_SRCS)

include (${TICOS_PATH}/scripts/cmake/ticos.cmake)

project (01_device)
