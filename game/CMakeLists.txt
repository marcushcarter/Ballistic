file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE GAME_HEADERS CONFIGURE_DEPENDS "src/*.h")

add_executable(ballistic_game # WIN32
    ${GAME_SOURCES}
    ${GAME_HEADERS}
    ${BALLISTIC_ENGINE_RC_FILES}
)

target_include_directories(ballistic_engine
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
    PUBLIC "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_libraries(ballistic_game PRIVATE ballistic_engine)

target_precompile_headers(ballistic_game PRIVATE pch.h)

set_target_properties(ballistic_game PROPERTIES OUTPUT_NAME "ballistic_game")