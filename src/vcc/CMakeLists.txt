project (vcc)
set (EXE_NAME "vcc")
set (SRC
    main.cpp
)

message ("test: ${VC_INCLUDE}")
message ("VC_INCLUDE: ${VC_INCLUDE}")


include_directories (${VC_INCLUDE})
add_executable (${EXE_NAME} ${SRC})
target_link_libraries (${EXE_NAME} vc)

