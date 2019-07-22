
project( ${GLOBAL_PROJECT}_infra )

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
)

add_library(
    ${PROJECT_NAME}
    SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/execution/execution_base.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/execution/execution_forever.cpp
)


