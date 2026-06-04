file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS "src/*.h")

add_subdirectory(res)

add_library(ballistic_engine STATIC
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)

target_include_directories(ballistic_engine
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/res"
    PUBLIC "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_options(ballistic_engine PRIVATE "/ignore:4099")

target_link_libraries(ballistic_engine
    PUBLIC ballistic_compiler_options
    PUBLIC Vulkan::Vulkan
    PUBLIC Vulkan::shaderc_combined
    PUBLIC vma
    PUBLIC glfw
    PUBLIC stb
    PUBLIC imgui
    PUBLIC glm
    PUBLIC iconfontcppheaders
    PUBLIC tinyfiledialogs
    PUBLIC tomlplusplus
    PUBLIC Shell32
    PUBLIC imnodes
    PRIVATE dwmapi
)

target_precompile_headers(ballistic_engine PRIVATE pch.h)