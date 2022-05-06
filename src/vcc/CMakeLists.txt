project (vcc)
set (EXE_NAME "vcc")

message ("vcc project")
message ("VC_INCLUDE: ${VC_INCLUDE}")




set (SRC
    main.cpp
)



add_executable (${EXE_NAME} ${SRC})
include_directories (${VC_INCLUDE})
target_link_libraries (${EXE_NAME} vc)

