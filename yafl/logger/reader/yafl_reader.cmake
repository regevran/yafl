

execute_process(    
    COMMAND             find ${MAP_DIR} -name "*map" -exec cat {} \;
    OUTPUT_VARIABLE     file_mapping
)

configure_file( 
    ${READER_DIR}/reader.py.in 
    ${MAP_DIR}/logger/reader/reader.py
)

