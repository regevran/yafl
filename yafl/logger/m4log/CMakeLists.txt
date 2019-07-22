

set(
    target
    LoggerM4Log
)

project( ${target} )

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/../../
)

set(
    source
    ${CMAKE_CURRENT_BINARY_DIR}/BulkLog.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/LogHandler.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/m4log_defs.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/log.cpp
)

# library
add_library( 
    ${target}
    ${source}
)

target_link_libraries( 
    ${target}
    ${GLOBAL_PROJECT}_infra
)

#add_dependencies(
#    ${target}
#    LoggerInc
#)

set(
    files_to_precompile 
    BulkLog.cpp
    BulkLog.h
    LogHandler.cpp
    LogHandler.h
    log.h
    log.cpp
    m4log_defs.cpp
)

# yafl-pre-compile
include( ${YAFL_SOURCE_DIR}/custom.build/log_precompile.cmake ) 

        
