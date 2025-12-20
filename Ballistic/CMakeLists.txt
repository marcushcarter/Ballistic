file(GLOB_RECURSE ENGINE_SRC
    src/*.cpp
)

add_library(Ballistic STATIC ${ENGINE_SRC})

target_include_directories(Ballistic PUBLIC
    include          # public headers
    BallisticEditor/src      # so editor can include engine headers
    BallisticRuntime/src     # runtime as well
)

target_link_libraries(Ballistic PUBLIC
    glfw
    glad
    glm
    imgui
    stb
    EnTT::EnTT
    IconFontCppHeaders
    tinyfiledialogs
    nlohmann_json
    ${CMAKE_DL_LIBS}
)

target_precompile_headers(Ballistic PUBLIC include/bepch.h)
