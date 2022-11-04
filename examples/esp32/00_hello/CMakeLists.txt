# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required (VERSION 3.20)

include ($ENV{IDF_PATH}/tools/cmake/project.cmake)

set (TICOS_PLATFORM esp32)
set (TICOS_USE_FREERTOS TRUE)

set (TICOS_FRAMEWORK ticos-framework)

message (STATUS "Looking for TICOS_FRAMEWORK_PATH")
if (DEFINED ENV{TICOS_FRAMEWORK_PATH})
set (TICOS_FRAMEWORK_PATH $ENV{TICOS_FRAMEWORK_PATH})
message (STATUS "Found TICOS_FRAMEWORK_PATH from $ENV{TICOS_FRAMEWORK_PATH}")
elseif (EXISTS ${CMAKE_SOURCE_DIR}/../../../../${TICOS_FRAMEWORK})
set (TICOS_FRAMEWORK_PATH ${CMAKE_SOURCE_DIR}/../../../../${TICOS_FRAMEWORK})
message (STATUS "Found TICOS_FRAMEWORK_PATH from the parent direcroty")
elseif (EXISTS $ENV{HOME}/.ticos/packages/${TICOS_FRAMEWORK})
set (TICOS_FRAMEWORK_PATH $ENV{HOME}/.ticos/packages/${TICOS_FRAMEWORK})
message (STATUS "Found TICOS_FRAMEWORK_PATH from the default ticos direcroty")
else ()
message (FATAL_ERROR "TICOS_FRAMEWORK_PATH not found")
endif ()

include (${TICOS_FRAMEWORK_PATH}/scripts/cmake/ticos.cmake)

aux_source_directory (${CMAKE_SOURCE_DIR}/main  PROJ_SRCS)

project (00_hello)
