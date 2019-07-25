

# set the files to compile in this directory
set( 
    source
    ${source}
    ${CMAKE_CURRENT_BINARY_DIR}/counter_rate.cpp
    PARENT_SCOPE
)

# log precompile
set(
    files_to_precompile 
    ${files_to_precompile}
    src/counter/counter_rate.cpp
    PARENT_SCOPE
)


