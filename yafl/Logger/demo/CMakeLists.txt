

set(
    target
    LoggerDemo
)

project( ${target} )

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
)

set(
    sources
    ${CMAKE_CURRENT_BINARY_DIR}/main.cpp
    #    ${CMAKE_CURRENT_BINARY_DIR}/series.cpp
)

# executable
add_executable( 
    ${target}
    ${sources}
)

target_link_libraries( 
    ${target}
    LoggerM4Log
    Infra
)

# log precompile
set(
    files_to_precompile 
    main.cpp         
)

include( ${IP_SOURCE_DIR}/custom.build/log_precompile.cmake )

