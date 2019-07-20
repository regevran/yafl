
project( ${GLOBAL_PROJECT}_infra )

add_library(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/execution/execution_base.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/execution/execution_notification.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/execution/execution_period.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/execution/execution_countdown.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/execution/execution_forever.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/execution/execution_once.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/execution/execution_at.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/execution/execution_count.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/execution/execution_suspend.cpp
)


