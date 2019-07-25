
set( 
    dirs
    ${dirs}
    ${CMAKE_CURRENT_BINARY_DIR}
    PARENT_SCOPE
)

# set the files to compile in this directory
set( 
    source
    ${source}
    ${CMAKE_CURRENT_BINARY_DIR}/execution_base.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/execution_count.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/execution_forever.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/execution_notification.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/execution_once.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/execution_suspend.cpp
    PARENT_SCOPE
)

# log precompile
set(
    files_to_precompile 
    ${files_to_precompile}
    src/execution/execution_at.cpp
    src/execution/execution_base.cpp
    src/execution/execution_count.cpp
    src/execution/execution_countdown.cpp
    src/execution/execution_forever.cpp
    src/execution/execution_notification.cpp
    src/execution/execution_once.cpp
    src/execution/execution_period.cpp
    src/execution/execution_suspend.cpp
    PARENT_SCOPE
)

