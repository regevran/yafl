
# executables defined for this cmake tree:
# Analyzer
# pace2_analyzer

# cmake version
cmake_minimum_required( VERSION 3.10 )

# compilter (must be before any project() command)
set( CMAKE_CXX_COMPILER         g++ )
set( CMAKE_C_COMPILER           gcc ) 

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

set(
    GLOBAL_PROJECT
    ${PROJECT_NAME}
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
subdirs( 
    infra/
    logger/m4log
    logger/inc
    logger/demo
    logger/reader
)





