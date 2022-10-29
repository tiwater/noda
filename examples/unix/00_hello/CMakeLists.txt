cmake_minimum_required (VERSION 3.20)
project (00_hello)

# compiling flags
set (CMAKE_C_STANDARD 11)
add_definitions (-Wall -Werror -Wextra -Wstrict-prototypes)

if (DEFINED ENV{NODA_PATH})
set (NODA_PATH $ENV{NODA_PATH})
else ()
set (NODA_PATH ${CMAKE_SOURCE_DIR}/../../..)
endif ()
set (NODA_PLATFORM unix)

include (${NODA_PATH}/scripts/cmake/noda.cmake)

aux_source_directory (${CMAKE_SOURCE_DIR} PROJECT_SRCS)
include_directories (${NODA_INCS})
add_executable (${PROJECT_NAME} ${NODA_SRCS} ${PROJECT_SRCS})
