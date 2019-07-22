
set(
    target
    ${GLOBAL_PROJECT}_infra_execution_h
)

set(
    files_to_precompile 
    execution_forever.h
    execution_base.h
    owner_execution.h
)

set(
    source
    ${files_to_precompile}
    PARENT_SCOPE
)

add_custom_target( 
    ${target}
    DEPENDS ${files_to_precompile}
)

# yafl-pre-compile
include( ${YAFL_SOURCE_DIR}/custom.build/log_precompile.cmake ) 




