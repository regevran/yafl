

set( dirs
    ${dirs}
    PARENT_SCOPE
)

# set the files to compile in this directory
set( 
    source
    ${source}
    ${CMAKE_CURRENT_BINARY_DIR}/thread_queue_counter.cpp
    PARENT_SCOPE
)

# log precompile
set(
    files_to_precompile 
    ${files_to_precompile}
    src/thread_queue/thread_queue_counter.cpp
    PARENT_SCOPE
)


