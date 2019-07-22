

add_custom_command(
    OUTPUT              empty.h 
    COMMAND             cp ${CMAKE_CURRENT_SOURCE_DIR}/empty.h ${CMAKE_CURRENT_BINARY_DIR}/empty.h 
    MAIN_DEPENDENCY     empty.h 
) 

add_custom_command(
    OUTPUT              empty.cpp 
    COMMAND             cp ${CMAKE_CURRENT_SOURCE_DIR}/empty.cpp ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp 
    MAIN_DEPENDENCY     empty.cpp 
) 

