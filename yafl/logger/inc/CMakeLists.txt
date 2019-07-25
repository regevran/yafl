

set(
    target
    logger_inc 
)

# empty target for dependencies only
add_custom_target( 
    ${target} 
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/../../
)

set(
    files_to_precompile 
    log.h
    m4log_defs.h
)

# yafl-pre-compile
include( ${YAFL_SOURCE_DIR}/custom.build/log_precompile.cmake ) 

        
