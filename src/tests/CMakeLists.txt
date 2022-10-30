project (vc_tests)
set (EXE_NAME "vc_tests")

set (SRC
    main.cpp
    unit_test.h
    unit_test.cpp
    lexer_tests.cpp
)

add_executable (${EXE_NAME} ${SRC})
include_directories (${VC_INCLUDE})
target_link_libraries (${EXE_NAME} vc)

