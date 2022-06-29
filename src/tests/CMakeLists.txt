project (vc_tests)
set (EXE_NAME "vc_tests")

set (SRC
    main.cpp
)

add_executable (${EXE_NAME} ${SRC})
include_directories (${VC_INCLUDE})
target_link_libraries (${EXE_NAME} vc)

