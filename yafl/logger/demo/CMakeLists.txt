

set(
    target
    logger_demo
)

project( ${target} )

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
)

set(
    sources
    ${CMAKE_CURRENT_BINARY_DIR}/main.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/series.cpp
)

# executable
add_executable( 
    ${target}
    ${sources}
)

target_link_libraries( 
    ${target}
    logger_m4log
    infra
)

# log precompile
set(
    files_to_precompile 
    main.cpp         
    msg.h
    power.h
    series.cpp
    series.h

)

include( ${YAFL_SOURCE_DIR}/custom.build/log_precompile.cmake )

