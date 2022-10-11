cmake_minimum_required (VERSION 3.20)
project (00_hello)

# compiling flags
add_definitions (-std=c11)
add_definitions (-pedantic -pedantic-errors)
add_definitions (-pipe -fPIC)
add_definitions (-Wall -Werror -Wextra -Wstrict-prototypes)

if (NOT DEFINED ENV{NODA_PATH})
set (NODA_PATH ${CMAKE_SOURCE_DIR}/../../../..)
endif ()
set (NODA_PLATFORM unix)

include (${NODA_PATH}/scripts/cmake/noda.cmake)

aux_source_directory (${NODA_PATH}/examples/${PROJECT_NAME} PROJECT_SRCS)
include_directories (${NODA_INCS})
add_executable (${PROJECT_NAME} ${NODA_SRCS} ${PROJECT_SRCS})
