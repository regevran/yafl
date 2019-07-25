

set(
    target
    infra
)

project( ${target} )

option( BUILD_STATIC_LIBS "infra static" OFF )
option( BUILD_SHARED_LIBS "infra shared" ON )


add_subdirectory( "inc/counter" )
add_subdirectory( "inc/execution" )
add_subdirectory( "inc/thread_queue" )
add_subdirectory( "inc/operation" )
add_subdirectory( "src/counter" )
add_subdirectory( "src/execution" )
add_subdirectory( "src/thread_queue" )



include_directories( ${CMAKE_CURRENT_BINARY_DIR}/../ )


add_library( 
    ${target} 
    ${source} 
)

target_link_libraries( 
    ${target}
    pthread
)

# log precompile
set(
    files_to_precompile 
    ${files_to_precompile}
    inc/joinable.h
)

include( ${YAFL_SOURCE_DIR}/custom.build/log_precompile.cmake )

