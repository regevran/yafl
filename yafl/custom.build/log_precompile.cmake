

# expected variables to be set:
# files_to_precompile   - a list of files that need to be precompiled (bare - without directory)
# target                - the name of the target executable or library (cmake target)

foreach( bare_file ${files_to_precompile} ) 

    set(
        source_file
        ${CMAKE_CURRENT_SOURCE_DIR}/${bare_file}
    )

    set(
        target_file
        ${CMAKE_CURRENT_BINARY_DIR}/${bare_file}
    ) 

    set(
        map_target_file
        ${CMAKE_CURRENT_BINARY_DIR}/${bare_file}.map
    )

    set(
        generator_sh_file
        ${CMAKE_CURRENT_BINARY_DIR}/${bare_file}.gen.sh
    )

    # set the variables for the generator
    set( SOURCE_FILE        ${source_file} )
    set( TARGET_FILE        ${target_file} )
    set( MAP_TARGET_FILE    ${map_target_file} )


    add_custom_command(
        OUTPUT  ${generator_sh_file}
        COMMAND     
                ${CMAKE_COMMAND} 
                -DGENERATOR_IN_FILE=${YAFL_SOURCE_DIR}/m4/generate_code_and_map.sh.in
                -DGENERATOR_OUT_FILE=${generator_sh_file}
                -DSOURCE_FILE=${source_file}
                -DTARGET_FILE=${target_file}
                -DMAP_TARGET_FILE=${map_target_file} 
                -DYAFL_PREPROCESSOR_DIR=${YAFL_SOURCE_DIR}/m4/
                -P ${YAFL_SOURCE_DIR}/custom.build/configure_generator.cmake 

        DEPENDS ${source_file}
    )

    add_custom_command(
        OUTPUT              ${target_file}
        COMMAND             ${generator_sh_file}
        MAIN_DEPENDENCY     ${generator_sh_file}
        DEPENDS             ${source_file}
    )

    string( REPLACE "/" "_" generator_target generator-${target}-${bare_file})

    add_custom_target(
        ${generator_target}
        DEPENDS     ${target_file}
    )

    add_dependencies(
        ${target}
        ${generator_target}
    )

endforeach ( bare_file ${files_to_precompile} ) 


