
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

find_package( Threads )

# compiler flags
add_compile_options( 
    -Wall
    -Werror
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
    infra
    # logger
    # m4
)





