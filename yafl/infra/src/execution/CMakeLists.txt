
project( )


set(
    target
    ${GLOBAL_PROJECT}_infra 
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/../../
)

set(
    source
    ${CMAKE_CURRENT_BINARY_DIR}/execution_base.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/execution_forever.cpp
)

# library
add_library( 
    ${target}
    SHARED
    ${source}
)

set(
    files_to_precompile 
    execution_base.cpp
    execution_forever.cpp      
)

# yafl-pre-compile
include( ${YAFL_SOURCE_DIR}/custom.build/log_precompile.cmake ) 




