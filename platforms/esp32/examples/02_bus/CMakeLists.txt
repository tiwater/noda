# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required (VERSION 3.20)

include ($ENV{IDF_PATH}/tools/cmake/project.cmake)

if (NOT DEFINED ENV{NODA_PATH})
set (NODA_PATH ${CMAKE_SOURCE_DIR}/../../../..)
endif ()
set (NODA_PLATFORM esp32)

include (${NODA_PATH}/scripts/cmake/noda.cmake)

project (02_bus)

