
# cmake version
cmake_minimum_required( VERSION 3.15 )

# cmake settings
set( FIND_LIBRARY_USE_LIB64_PATHS ON )

# project
project( yafl )

set(
    YAFL_SOURCE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
    YAFL_BINARY_DIR
    ${CMAKE_CURRENT_BINARY_DIR}
)

find_package( Threads )

# compiler flags
add_compile_options( 
    -Wall
    -Werror
    -O3
)

# build type settings
# for both compile and link
set( 
    CMAKE_CXX_FLAGS_DEBUG 
    "-gdwarf-3 -ggdb"
)

set( 
    CMAKE_CXX_FLAGS_RELEASE
    "-DRELEASE_VERSION -O2"
)

# directories
add_subdirectory( infra )
add_subdirectory( logger )

