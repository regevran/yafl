


add_custom_target( 
    logger_reader
    ALL
    COMMAND     ${CMAKE_COMMAND} -DMAP_DIR=${YAFL_BINARY_DIR} -DREADER_DIR=${CMAKE_CURRENT_SOURCE_DIR} -P ${CMAKE_CURRENT_SOURCE_DIR}/yafl_reader.cmake 
    COMMENT     "Generating reader.py" 

    #DEPENDS    <all targets that have yafl log inside must be built before the reader. otherwise their .map files are not ready>
    DEPENDS     infra
    DEPENDS     logger_m4log
    DEPENDS     logger_inc
    DEPENDS     logger_demo

)

