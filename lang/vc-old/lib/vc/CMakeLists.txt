project (vc)

set (VC_INC "${VC_INCLUDE}/vc")
set (VC_LIB "${VC_LIB}/vc")

set (LIB_NAME "vc")

set (HEADERS

    ${VC_INC}/compiler.h
    ${VC_INC}/lexer.h
    ${VC_INC}/parser.h
    ${VC_INC}/val.h
    ${VC_INC}/opcode.h
    ${VC_INC}/opgen.h
    ${VC_INC}/vm.h

    ${VC_INC}/ast/decl.h
    ${VC_INC}/ast/decl_group.h
    ${VC_INC}/ast/df_ast_visitor.h
    ${VC_INC}/ast/expr.h
    ${VC_INC}/ast/name.h
    ${VC_INC}/ast/printer.h
    ${VC_INC}/ast/stmt.h
    ${VC_INC}/ast/type.h

    ${VC_INC}/ast/base_ast_visitor.h
    ${VC_INC}/ast/recursive_ast_visitor.h

    ${VC_INC}/basic/file_buffer.h
    ${VC_INC}/basic/convert.h
    ${VC_INC}/basic/report.h
    ${VC_INC}/basic/source_location.h
    ${VC_INC}/basic/token.h
    ${VC_INC}/basic/token_precedence.h

    ${VC_INC}/definitions/basic_kinds.def
    ${VC_INC}/definitions/decls.def
    ${VC_INC}/definitions/stmts.def
    ${VC_INC}/definitions/exprs.def
    ${VC_INC}/definitions/token_kinds.def
    ${VC_INC}/definitions/types.def
)

set (LIB

    ${VC_LIB}/ast/decl.cpp
    ${VC_LIB}/ast/decl_group.cpp
    ${VC_LIB}/ast/printer.cpp

    ${VC_LIB}/ast/base_ast_visitor.cpp
    ${VC_LIB}/ast/recursive_ast_visitor.cpp
    ${VC_LIB}/ast/df_ast_visitor.cpp
    ${VC_LIB}/ast/type.cpp

    ${VC_LIB}/basic/file_buffer.cpp
    ${VC_LIB}/basic/source_location.cpp
    ${VC_LIB}/basic/report.cpp
    ${VC_LIB}/basic/token.cpp
    ${VC_LIB}/basic/token_precedence.cpp

    ${VC_LIB}/compiler.cpp
    ${VC_LIB}/lexer.cpp
    ${VC_LIB}/opcode.cpp
    ${VC_LIB}/opgen.cpp
    ${VC_LIB}/vm.cpp

    ${VC_LIB}/parser/parser.cpp
    ${VC_LIB}/parser/parse_decl.cpp
    ${VC_LIB}/parser/parse_preprocessor.cpp
    ${VC_LIB}/parser/parse_expr.cpp
    ${VC_LIB}/parser/parse_stmt.cpp
    ${VC_LIB}/parser/parse_type.cpp

    ${VC_LIB}/validation/val.cpp
    ${VC_LIB}/validation/val_decl.cpp
    ${VC_LIB}/validation/val_stmt.cpp
    ${VC_LIB}/validation/val_expr.cpp
    ${VC_LIB}/validation/val_type.cpp
)

# Needed so the project can use <vc/blah>
include_directories (${VC_INCLUDE})
include_directories (${T_INCLUDE})

add_library (${LIB_NAME} STATIC ${HEADERS} ${LIB})
