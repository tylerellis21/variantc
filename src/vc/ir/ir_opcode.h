#ifndef IR_OPCODE_H_INCLUDE
#define IR_OPCODE_H_INCLUDE

#include <vc/types.h>
#include <string>

namespace vc {

enum class ir_opcode_id {
    NOP = 0,
    JO,
    JNO,
    JB,
    JNB,
};

struct ir_label {
    std::string name;
    u64 offset;
};

struct ir_nop { };

// jo - jump if overflow
struct ir_jo {
    u64 address;
};

// jno - jump if not overflow
struct ir_jno {
    u64 address;
};

// jb - jump if below
struct ir_jb {
    u64 address;
};

// jnb - jump if not below
struct ir_jnb {
    u64 address;
};

// jz - jump if zero
struct ir_jz {
    u64 address;
};

// jnz - jump if not zero
struct ir_jnz {
    u64 address;
};

// jbe - jump if below or equal
struct ir_jbe {
    u64 address;
};

// jnbe - jump if not below or equal
struct ir_jnbe {
    u64 address;
};

// js - jump if sign
struct ir_js {
    u64 address;
};

// jns - jump if not sign
struct ir_jns {
    u64 address;
};

// jp - jump if parity
struct ir_jp {
    u64 address;
};

// jnp - jump if not parity
struct ir_jnp {
    u64 address;
};

// jl - jump if less
struct ir_jl {
    u64 address;
};

// jnl - jump if not less
struct ir_jnl {
    u64 address;
};

// jle - jump if less or equal
struct ir_jle {
    u64 address;
};

// jnle - jump if not less or equal
struct ir_jnle {
    u64 address;
};

// call
struct ir_call {
    u64 address;
};

// ret
struct ir_ret {

};

// mov
struct ir_load {
    u64 src;
    u64 dest;
};

struct ir_store {
    u64 dest;
};

// xchg - exchange register/memory with register

// lea - load effective address
struct ir_lea {
    u64 size;
    u64 index;
    u64 offset;
};

// cmp - compare two operands

// test - logical compare

// add - add

// adc - add with carry

// sub - subtract

// sbb - subtract with borrow

// mul - multiply

// div - divide

// inc - add 1

// dec - subtract 1

// or - logical inclusive OR

// and - logical AND

// xor - logical exclusive OR

// not - one's complement negation

// neg - two's complement negation

// rol - rotate left
// <<<

// ror - rotate right
// >>>

// rcl - rotate carry left
// @<<

// rcr - rotate carry right
// @>>

// shl - shift left, unsigned multiply
// <<

// shr - shift right, unsigned divide
// >>

// sal - shift left, signed multiply
// <<

// sar - shift right, signed divide
// <<

// clc - clear carry flag

// push - push bytes to the stack
// pop - pop values from the stack

// how do we want to use mmx instructions?
// should we leave that to the optimizer? or allow their use in the IR

struct ir_opcode {
    ir_opcode_id opcodeId;
    BuiltinKind opcodeType;

    union {
        ir_nop nop;

        ir_jo jo;
        ir_jno jno;

        ir_jb jb;
        ir_jnb jnb;
    };

    ir_opcode(BuiltinKind opcodeType) :
        opcodeType(opcodeType)
    { }

    ir_opcode(ir_nop nop) :
        opcodeId(ir_opcode_id::NOP),
        opcodeType(BuiltinKind::Null),
        nop(nop)
    { }
};

constexpr int OPCODE_SIZE = sizeof(ir_opcode);

} // namespace vc

#endif // IR_OPCODE_H_INCLUDE
