file(
    GLOB_RECURSE
    SOURCE_FILES 
    *.c
)

message("src: ${SOURCE_FILES}")

add_library(CGrimoire ${SOURCE_FILES})

target_include_directories(CGrimoire PUBLIC
    ${INCLUDE_DIRECTORIES}
)

target_compile_options(CGrimoire PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_precompile_headers(CGrimoire PUBLIC
    ${INCLUDE_DIRECTORIES}/CGrimoire/details/defines.h
)