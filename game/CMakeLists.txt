file(GLOB_RECURSE BALLISTIC_GAME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_library(ballistic_game_lib STATIC ${BALLISTIC_GAME_SOURCES})

target_include_directories(ballistic_game_lib
PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/generated
)

target_link_libraries(ballistic_game_lib
PUBLIC
    ballistic_compiler_options
    ballistic_core
)