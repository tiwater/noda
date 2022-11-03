cmake_minimum_required (VERSION 3.20)
project (00_hello)

# compiling flags
set (CMAKE_C_STANDARD 99)
add_definitions (-Wall -Werror -Wextra -Wstrict-prototypes)

set (TICOS_PLATFORM unix)

set (TICOS_FRAMEWORK ticos-framework)

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

aux_source_directory (${CMAKE_SOURCE_DIR} PROJECT_SRCS)
include_directories (${FRAMEWORK_INCS})
add_executable (${PROJECT_NAME} ${FRAMEWORK_SRCS} ${PROJECT_SRCS})
