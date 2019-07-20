


add_custom_target( 
    LoggerReader
    ALL
    COMMAND     ${CMAKE_COMMAND} -DMAP_DIR=${IP_BINARY_DIR} -DREADER_DIR=${CMAKE_CURRENT_SOURCE_DIR} -P ${CMAKE_CURRENT_SOURCE_DIR}/yafl_reader.cmake 
    COMMENT     "Generating reader.py" 
    DEPENDS     Analyzer
)

