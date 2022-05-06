project (vc)

set (LIB_NAME "vc")
set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set (SRC
    ${SRC_DIR}/asm/x64.h
    ${SRC_DIR}/asm/x86.h

    ${SRC_DIR}/basic/filebuffer.cpp
    ${SRC_DIR}/basic/sourcelocation.h
    ${SRC_DIR}/basic/token.h

    ${SRC_DIR}/compiler/lexer.h
    ${SRC_DIR}/compiler/lexer.cpp
)

include_directories (${VC_INCLUDE})
add_library (${LIB_NAME} STATIC ${SRC})