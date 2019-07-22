
list( 
    LENGTH 
    project_cpp_files 
    project_len
)


foreach( bare_cpp_file ${project_cpp_files} ) 

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

    message( "adding custom target: ${bare_cpp_file}_pre_compile" )

    add_custom_target(
        ${bare_cpp_file}_pre_compile
        COMMAND             ${cpp_generator_file}
        BYPRODUCTS          ${cpp_target_file}
        SOURCES             ${cpp_file}
    )




#    add_custom_command(
#        OUTPUT              ${cpp_target_file} 
#        COMMAND             ${cpp_generator_file}
#        MAIN_DEPENDENCY     ${cpp_file}
#        DEPENDS             ${cpp_generator_file}
#        IMPLICIT_DEPENDS    CXX ${cpp_file} 
#    ) 

endforeach()

