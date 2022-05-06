#ifndef VC_X64_H_INCLUDE
#define VC_X64_H_INCLUDE

namespace vc {

struct opcode_mov {
    int type;
    int src;
    int dest;
};

enum class OpcodeTypeX64 {

};

struct OpcodeX64 {
    OpcodeTypeX64 opcodeType;
    union {
        opcode_mov mov;
    };
};


} // namespace vc

#endif // VC_X64_H_INCLUDE
