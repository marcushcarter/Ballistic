string(REPLACE "|" ";" SPIRV_LIST "${SPIRV_FILES}")

set(H_CONTENT "#pragma once\n#include <cstdint>\n\n")

foreach(SPV_FILE ${SPIRV_LIST})
    get_filename_component(FNAME ${SPV_FILE} NAME)
    string(REPLACE "." "_" VAR_NAME ${FNAME})
    string(TOUPPER ${VAR_NAME} VAR_NAME)

    file(READ ${SPV_FILE} SPV_HEX HEX)
    string(LENGTH ${SPV_HEX} HEX_LEN)

    set(WORDS "")
    math(EXPR WORD_COUNT "${HEX_LEN} / 8")

    foreach(i RANGE 0 ${WORD_COUNT})
        math(EXPR OFFSET "${i} * 8")
        if(OFFSET LESS ${HEX_LEN})
            string(SUBSTRING ${SPV_HEX} ${OFFSET} 8 WORD_HEX)
            string(SUBSTRING ${WORD_HEX} 6 2 B0)
            string(SUBSTRING ${WORD_HEX} 4 2 B1)
            string(SUBSTRING ${WORD_HEX} 2 2 B2)
            string(SUBSTRING ${WORD_HEX} 0 2 B3)
            list(APPEND WORDS "0x${B0}${B1}${B2}${B3}")
        endif()
    endforeach()

    list(JOIN WORDS ", " WORDS_STR)
    string(APPEND H_CONTENT "static constexpr uint32_t ${VAR_NAME}[] = { ${WORDS_STR} };\n")
    string(APPEND H_CONTENT "static constexpr size_t   ${VAR_NAME}_SIZE = sizeof(${VAR_NAME});\n\n")
endforeach()

file(WRITE "${OUTPUT_FILE}" "${H_CONTENT}")