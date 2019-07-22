
list( 
    LENGTH 
    project_h_files 
    project_len
)

set( 
    current_index
    0
)

foreach( bare_h_file ${project_h_files} )

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

    # set the variables for the generator (.gen file)
    set( source_file        ${h_file} )
    set( target_file        ${h_target_file} )
    set( map_target_file    ${h_map_target_file} )

    configure_file( 
        ${YAFL_SOURCE_DIR}/m4/generate_code_and_map.sh.in
        ${h_generator_file}
    )

    message( "adding custom target: ${bare_h_file}_pre_compile" )

    add_custom_target(
        ${bare_h_file}_pre_compile
        COMMAND             ${h_generator_file}
        BYPRODUCTS          ${h_target_file}
        SOURCES             ${h_file}
    )

#    add_custom_command(
#        OUTPUT              ${h_target_file} 
#        COMMAND             ${h_generator_file}
#        MAIN_DEPENDENCY     ${h_file}
#        DEPENDS             ${h_generator_file}
#        IMPLICIT_DEPENDS    CXX ${h_file} 
#    ) 

endforeach()

