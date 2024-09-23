#ifndef OPCODE_H_INCLUDE
#define OPCODE_H_INCLUDE

#include <t/core/string.h>

namespace t {
namespace vc {

#define OPCODE_TYPES \
    OPCODE_TYPE(type_null, "null") \
    OPCODE_TYPE(type_u8, "u8") \
    OPCODE_TYPE(type_u16, "u16") \
    OPCODE_TYPE(type_u32, "u32") \
    OPCODE_TYPE(type_u64, "u64") \
    OPCODE_TYPE(type_i8, "i8") \
    OPCODE_TYPE(type_i16, "i16") \
    OPCODE_TYPE(type_i32, "i32") \
    OPCODE_TYPE(type_i64, "i64") \
    OPCODE_TYPE(type_r32, "r32") \
    OPCODE_TYPE(type_r64, "r64")

enum OpcodeType {
#define OPCODE_TYPE(TYPE_NAME, TYPE_STRING) TYPE_NAME,
    OPCODE_TYPES
#undef OPCODE_TYPE
};


#define OPCODES \
    OPCODE(NOP) \
    OPCODE(HLT) \
    OPCODE(LOAD) \
    OPCODE(STORE) \
    OPCODE(LLOAD) \
    OPCODE(LSTORE) \
    OPCODE(REFLOAD) \
    OPCODE(REFSTORE) \
    OPCODE(CMP) \
    OPCODE(PUSH8) \
    OPCODE(PUSH16) \
    OPCODE(PUSH32) \
    OPCODE(PUSH64) \
    OPCODE(PUSH_ZERO) \
    OPCODE(PUSH_ONE) \
    OPCODE(PUSH_NEGO) \
    OPCODE(POP) \
    OPCODE(POP2) \
    OPCODE(DUP) \
    OPCODE(DUP2) \
    OPCODE(CALL) \
    OPCODE(RET) \
    OPCODE(JMP) \
    OPCODE(LJMP) \
    OPCODE(JE) \
    OPCODE(JNE) \
    OPCODE(JL) \
    OPCODE(JLE) \
    OPCODE(JG) \
    OPCODE(JGE) \
    OPCODE(ADD) \
    OPCODE(SUB) \
    OPCODE(MUL) \
    OPCODE(DIV) \
    OPCODE(MOD) \
    OPCODE(BSL) \
    OPCODE(BSR) \
    OPCODE(NOT) \
    OPCODE(AND) \
    OPCODE(OR) \
    OPCODE(XOR) \
    OPCODE(INC) \
    OPCODE(DEC) \
    OPCODE(PRINT_STACK_TOP) \
    OPCODE(SLEEP)

enum OpcodeId : u8 {
#define OPCODE(MEMONIC) MEMONIC,
    OPCODES
#undef OPCODE
};

union Args {
    u8 _u8;
    u16 _u16;
    u32 _u32;
    u64 _u64;

    i8 _i8;
    i16 _i16;
    i32 _i32;
    i64 _i64;

    r32 _r32;
    r64 _r64;
};

// A representation
struct Opcode {
    OpcodeId id;

    struct {} nop;
    struct {} hlt;

    struct {
        OpcodeType type;
    } cmp;

    struct {
        OpcodeType type;
        u16 address;
    } load;

    struct {
        OpcodeType type;
        u16 address;
    } store;

    struct {
        OpcodeType type;
        u16 address;
    } lload;

    struct {
        OpcodeType type;
        u16 address;
    } lstore;

    struct {
        u8 value;
    } push8;

    struct {
        u16 value;
    } push16;

    struct {
        u32 value;
    } push32;

    struct {
        u64 value;
    } push64;

    struct { } pop;
    struct { } pop2;
    struct { } dup;
    struct { } dup2;

    struct {
        u16 index;
        u16 arg_count;
    } call;

    struct { } ret;

    struct {
        u16 address;
    } jmp;

    struct {
        u32 address;
    } ljmp;

    struct {
        u32 address;
    } je;

    struct {

        u32 address;
    } jne;

    struct {

        u32 address;
    } jl;

    struct {

        u32 address;
    } jle;

    struct {
        u32 address;
    } jg;

    struct {
        u32 address;
    } jge;

    struct {
        OpcodeType type;
    } add;

    struct {
        OpcodeType type;
    } sub;

    struct {
        OpcodeType type;
    } mul;

    struct {
        OpcodeType type;
    } div;

    struct {
        OpcodeType type;
    } mod;

    struct {
        OpcodeType type;
    } bsl;

    struct {
        OpcodeType type;
    } bsr;

    struct {
        OpcodeType type;
    } _not;

    struct {
        OpcodeType type;
    } _and;

    struct {
        OpcodeType type;
    } _or;

    struct {
        OpcodeType type;
    } _xor;

    struct {
        OpcodeType type;
    } inc;

    struct {
        OpcodeType type;
    } dec;

    inline Opcode() :
        id(NOP)
    { }

    inline Opcode(OpcodeId id) :
        id(id)
    { }
};

utf8 opcode_type_str(OpcodeType type);
void opcode_print_type(OpcodeType type);

utf8 opcode_memonic_str(OpcodeId id);
void opcode_print(Opcode opcode);

} // namespace vc
} // namespace t

#endif // OPCODE_H_INCLUDE
