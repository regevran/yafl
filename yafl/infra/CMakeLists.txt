

set(
    target
    ${GLOBAL_PROJECT}_infra
)

# library
add_library( 
    ${target}
    SHARED
    ${source}
)

target_link_libraries( 
    ${target}
    ${GLOBAL_PROJECT}_infra_execution_h
)


#
#set(
#    files_to_precompile 
#    inc/execution/execution_forever.h
#    inc/execution/execution_base.h
#    inc/execution/owner_execution.h
#    inc/operation/operation.h
#    inc/joinable.h
#    inc/thread_queue/thread_queue_counter.h
#    inc/thread_queue/thread_queue_handler.h
#    inc/thread_queue/thread_queue.h
#    inc/thread_queue/thread_queue_owner.h
#    /src/execution/execution_base.cpp
#    /src/execution/execution_forever.cpp      
#    /src/thread_queue/thread_queue_counter.cpp
#)
#
## yafl-pre-compile
#include( ${YAFL_SOURCE_DIR}/custom.build/log_precompile.cmake ) 
#
#
#
#
