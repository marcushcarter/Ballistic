cmake_minimum_required(VERSION 3.20)

set(SHADER_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE SHADERS
    "${SHADER_SRC_DIR}/*.vert"
    "${SHADER_SRC_DIR}/*.frag"
    "${SHADER_SRC_DIR}/*.comp"
    "${SHADER_SRC_DIR}/*.geom"
    "${SHADER_SRC_DIR}/*.tesc"
    "${SHADER_SRC_DIR}/*.tese"
)

set(SPIRV_FILES)

foreach(SHADER_FILE ${SHADERS})
    get_filename_component(FNAME ${SHADER_FILE} NAME)
    set(OUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/${FNAME}.spv")

    get_filename_component(EXT ${SHADER_FILE} EXT)
    string(TOLOWER ${EXT} EXT_LOWER)

    if(EXT_LOWER STREQUAL ".vert")
        set(STAGE_FLAG "-fshader-stage=vert")
    elseif(EXT_LOWER STREQUAL ".frag")
        set(STAGE_FLAG "-fshader-stage=frag")
    elseif(EXT_LOWER STREQUAL ".comp")
        set(STAGE_FLAG "-fshader-stage=comp")
    elseif(EXT_LOWER STREQUAL ".geom")
        set(STAGE_FLAG "-fshader-stage=geom")
    elseif(EXT_LOWER STREQUAL ".tesc")
        set(STAGE_FLAG "-fshader-stage=tesc")
    elseif(EXT_LOWER STREQUAL ".tese")
        set(STAGE_FLAG "-fshader-stage=tese")
    else()
        message(FATAL_ERROR "[Shader] Unknown stage for ${SHADER_FILE}")
    endif()

    add_custom_command(
        OUTPUT ${OUT_FILE}
        COMMAND glslc ${STAGE_FLAG} ${SHADER_FILE} -o ${OUT_FILE} --target-env=vulkan1.3 -O
        DEPENDS ${SHADER_FILE}
        COMMENT "Compiling ${FNAME}"
        VERBATIM
    )

    list(APPEND SPIRV_FILES ${OUT_FILE})
endforeach()

set(SHADERS_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/Shaders.h")
list(JOIN SPIRV_FILES "|" SPIRV_FILES_STR)

add_custom_command(
    OUTPUT ${SHADERS_HEADER}
    COMMAND ${CMAKE_COMMAND}
        -DSPIRV_FILES=${SPIRV_FILES_STR}
        -DOUTPUT_FILE=${SHADERS_HEADER}
        -P "${CMAKE_CURRENT_SOURCE_DIR}/GenerateShadersHeader.cmake"
    DEPENDS ${SPIRV_FILES}
    COMMENT "Generating Shaders.h"
    VERBATIM
)

add_custom_target(CompileEngineShaders ALL DEPENDS ${SHADERS_HEADER})