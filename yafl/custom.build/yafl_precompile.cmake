
# project_files must be defined by the calling cmake
# YAFL_SOURCE_DIR is defined in the main CMakeLists.txt

# project_files is an array of 'pairs': cpp file and its corresponding h file.
# if any of them is missing use empty string ""
# e.g.
# set(
#     project_files 
#     main.cpp            ""
#     series.cpp          series.h
# )
# main.cpp does not have a 'corresponding' h file and therefore we use ""
# series.cpp/h are representing a 'normal' file strucrture.
# end of example.
#
# the idea behind this 'stucture' is to enable cmake build our custom build to _all_
# files in the project. we, as developers, just need to list the files, both cpp and h that 
# are part of the project. there is no way to ommit the h files, and use only the implicit
# cxx dependency, as cmake can not guess the h files should go through the custom build

list( 
    LENGTH 
    project_files 
    project_len
)

set( 
    current_pair_index
    0
)

while ( ${current_pair_index} LESS ${project_len} ) 

    # cpp 
    list(
        GET
        project_files
        ${current_pair_index}
        bare_cpp_file
    )

    set(
        cpp_file
        ${CMAKE_CURRENT_SOURCE_DIR}/${bare_cpp_file}
    )

    set(
        cpp_target_file
        ${CMAKE_CURRENT_BINARY_DIR}/${bare_cpp_file}
    ) 

    set(
        cpp_map_target_file
        ${CMAKE_CURRENT_BINARY_DIR}/${bare_cpp_file}.map
    )

    set(
        cpp_generator_file
        ${CMAKE_CURRENT_BINARY_DIR}/${bare_cpp_file}.gen
    )

    # set the variables for the generator
    set( source_file        ${cpp_file} )
    set( target_file        ${cpp_target_file} )
    set( map_target_file    ${cpp_map_target_file} )

    # confiure the generator
    configure_file( 
        ${YAFL_SOURCE_DIR}/m4/generate_code_and_map.sh.in
        ${cpp_generator_file}
    )

    # get the h file 
    MATH( EXPR current_pair_index "${current_pair_index} + 1" )

    list(
        GET
        project_files
        ${current_pair_index}
        bare_h_file
    ) 

    set(
        h_file
        ${CMAKE_CURRENT_SOURCE_DIR}/${bare_h_file}
    )

    set(
        h_target_file
        ${CMAKE_CURRENT_BINARY_DIR}/${bare_h_file}
    ) 

    set(
        h_map_target_file
        ${CMAKE_CURRENT_BINARY_DIR}/${bare_h_file}.map
    )

    set(
        h_generator_file
        ${CMAKE_CURRENT_BINARY_DIR}/${bare_h_file}.gen
    )

    # set the variables for the generator
    set( source_file        ${h_file} )
    set( target_file        ${h_target_file} )
    set( map_target_file    ${h_map_target_file} )

    configure_file( 
        ${YAFL_SOURCE_DIR}/m4/generate_code_and_map.sh.in
        ${h_generator_file}
    )

    # cpp

    MESSAGE(
        "add_custom_command(
            OUTPUT              ${cpp_target_file} 
            COMMAND             ${cpp_generator_file}
            MAIN_DEPENDENCY     ${cpp_file}
            DEPENDS             ${cpp_generator_file}
            DEPENDS             ${h_target_file}
            IMPLICIT_DEPENDS    CXX ${cpp_file} 
        )" 
    )

    add_custom_command(
        OUTPUT              ${cpp_target_file} 
        COMMAND             ${cpp_generator_file}
        MAIN_DEPENDENCY     ${cpp_file}
        DEPENDS             ${cpp_generator_file}
        DEPENDS             ${h_target_file}
        IMPLICIT_DEPENDS    CXX ${cpp_file} 
    ) 

    # h
    MESSAGE(
        "add_custom_command(
            OUTPUT              ${h_target_file} 
            COMMAND             ${h_generator_file}
            MAIN_DEPENDENCY     ${h_file}
            DEPENDS             ${h_generator_file}
            IMPLICIT_DEPENDS    CXX ${h_file} 
        )"
    ) 
        
    add_custom_command(
        OUTPUT              ${h_target_file} 
        COMMAND             ${h_generator_file}
        MAIN_DEPENDENCY     ${h_file}
        DEPENDS             ${h_generator_file}
        IMPLICIT_DEPENDS    CXX ${h_file} 
    ) 

    MATH( EXPR current_pair_index "${current_pair_index} + 1" )

endwhile()

