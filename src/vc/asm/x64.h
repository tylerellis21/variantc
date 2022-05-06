#ifndef VC_X64_H_INCLUDE
#define VC_X64_H_INCLUDE

namespace vc {

enum class OpcodeTypeX64 {

};

struct OpcodeX64 {
    OpcodeTypeX64 opcodeType;
    union {
        opcode_mov mov;
    };
};

struct opcode_mov {

};

}

#endif // VC_X64_H_INCLUDE