cmake_minimum_required (VERSION 3.20)

project (           doxod
        VERSION     0.1.0.0
        LANGUAGES   C
        DESCRIPTION
        "Doxod - do something beyond xod")

# compiling flags
add_definitions (-std=c11)
add_definitions (-pedantic -pedantic-errors)
add_definitions (-pipe -fPIC)
add_definitions (-Wall -Werror -Wextra -Wstrict-prototypes)

# include head files    
include_directories (${CMAKE_SOURCE_DIR}/inc)

aux_source_directory (./src/core            CORE_SRCS)
aux_source_directory (./src/bus             BUS_SRCS)
aux_source_directory (./src/device          DEVICE_SRCS)
aux_source_directory (./src/platform/linux  PLATFORM_SRCS)
set (NODA_SRCS ${PLATFORM_SRCS} ${BUS_SRCS} ${DEVICE_SRCS} ${CORE_SRCS})

# build noda_hi
aux_source_directory (./examples/00_noda_hi EXAMPLE_00)
add_executable (00_noda_hi ${NODA_SRCS} ${EXAMPLE_00})
# add_executable (00_noda_hi ./examples/00_noda_hi ${NODA_SRCS})
