project (vc)

set (LIB_NAME "vc")
set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set (SRC
    ${SRC_DIR}/types.h

    ${SRC_DIR}/asm/x64.h
    ${SRC_DIR}/asm/x86.h

    ${SRC_DIR}/assembler/assembler.h
    ${SRC_DIR}/assembler/assembler.cpp

    ${SRC_DIR}/ast/astprinter.h
    ${SRC_DIR}/ast/astprinter.cpp
    ${SRC_DIR}/ast/decl.h
    ${SRC_DIR}/ast/declgroup.h
    ${SRC_DIR}/ast/expr.h
    ${SRC_DIR}/ast/name.h
    ${SRC_DIR}/ast/name.cpp
    ${SRC_DIR}/ast/stmt.h
    ${SRC_DIR}/ast/type.h

    ${SRC_DIR}/basic/builtinkind.h
    ${SRC_DIR}/basic/builtinkind.cpp
    ${SRC_DIR}/basic/filebuffer.h
    ${SRC_DIR}/basic/filebuffer.cpp
    ${SRC_DIR}/basic/sourcelocation.h
    ${SRC_DIR}/basic/sourcelocation.cpp
    ${SRC_DIR}/basic/token.h
    ${SRC_DIR}/basic/token.cpp
    ${SRC_DIR}/basic/tokenkind.h
    ${SRC_DIR}/basic/tokenkind.cpp
    ${SRC_DIR}/basic/tokenmap.h
    ${SRC_DIR}/basic/tokenmap.cpp
    ${SRC_DIR}/basic/tokenprecedence.h
    ${SRC_DIR}/basic/tokenprecedence.cpp

    ${SRC_DIR}/compiler/lexer.h
    ${SRC_DIR}/compiler/lexer.cpp
    ${SRC_DIR}/compiler/parser.h
    ${SRC_DIR}/compiler/parser.cpp
    ${SRC_DIR}/compiler/parser_decl.cpp
    ${SRC_DIR}/compiler/parser_expr.cpp
    ${SRC_DIR}/compiler/parser_stmt.cpp
    ${SRC_DIR}/compiler/parser_type.cpp

    #${SRC_DIR}/defs/tokenkinds.inl
    #${SRC_DIR}/defs/builtinkinds.inl

    ${SRC_DIR}/ir/ir_function.h
    ${SRC_DIR}/ir/ir_gen.h
    ${SRC_DIR}/ir/ir_gen.cpp
    ${SRC_DIR}/ir/ir_opcode.h
    ${SRC_DIR}/ir/ir_opcode.cpp
    ${SRC_DIR}/ir/ir_optimizer.h
)

include_directories (${VC_INCLUDE})
add_library (${LIB_NAME} STATIC ${SRC})
