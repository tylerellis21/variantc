project (vc_tests)
set (EXE_NAME "vc_tests")

set (SRC
    main.cpp
    unit_test.h
    unit_test.cpp
    lexer/lexer_tests.cpp
    lexer/lexer_comments.cpp
    lexer/lexer_literals.cpp
    parser/parser_tests.cpp
    ir/ir_tests.cpp
)

add_executable (${EXE_NAME} ${SRC})
include_directories (${VC_INCLUDE})
target_link_libraries (${EXE_NAME} vc)

