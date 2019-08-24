

set(
    LOGGER_M4LOG
    logger_m4log
)

# library
add_library( ${LOGGER_M4LOG} )

target_sources(
    ${LOGGER_M4LOG}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/BulkLog.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/LogHandler.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/m4log_defs.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/log.cpp
)

target_include_directories(
    ${LOGGER_M4LOG}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/../../
) 

add_dependencies(
    ${LOGGER_M4LOG}
    logger_inc
)

set(
    files_to_precompile 
    BulkLog.cpp
    BulkLog.h
    LogHandler.cpp
    LogHandler.h
    log.cpp
    m4log_defs.cpp
)

set(
    target
    ${LOGGER_M4LOG}
)

# yafl-pre-compile
include( ${YAFL_SOURCE_DIR}/custom.build/log_precompile.cmake ) 

        
