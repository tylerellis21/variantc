#ifndef VC_IR_OPCODE_H_INCLUDE
#define VC_IR_OPCODE_H_INCLUDE

#include <string>

#include <vc/types.h>
#include <vc/basic/builtinkind.h>

namespace vc {

enum class ir_opcode_id {
    NOP = 0,
    Label = 1,
    JO,
    JNO,
    JB,
    JNB,
};

struct ir_label {
    const std::string& name;

    ir_label(const std::string& name) :
        name(name)
    { }
};

struct ir_nop { };

// jo - jump if overflow
struct ir_jo {
    const std::string& name;

    ir_jo(const std::string& name) :
        name(name)
    { }
};

// jno - jump if not overflow
struct ir_jno {
    const std::string& name;

    ir_jno(const std::string& name) :
        name(name)
    { }
};

// jb - jump if below
struct ir_jb {
    const std::string& name;
};

// jnb - jump if not below
struct ir_jnb {
    const std::string& name;
};

// jz - jump if zero
struct ir_jz {
    const std::string& name;
};

// jnz - jump if not zero
struct ir_jnz {
    const std::string& name;
};

// jbe - jump if below or equal
struct ir_jbe {
    const std::string& name;
};

// jnbe - jump if not below or equal
struct ir_jnbe {
    const std::string& name;
};

// js - jump if sign
struct ir_js {
    const std::string& name;
};

// jns - jump if not sign
struct ir_jns {
    const std::string& name;
};

// jp - jump if parity
struct ir_jp {
    const std::string& name;
};

// jnp - jump if not parity
struct ir_jnp {
    const std::string& name;
};

// jl - jump if less
struct ir_jl {
    const std::string& name;
};

// jnl - jump if not less
struct ir_jnl {
    const std::string& name;
};

// jle - jump if less or equal
struct ir_jle {
    const std::string& name;
};

// jnle - jump if not less or equal
struct ir_jnle {
    const std::string& name;
};

// call
struct ir_call {
    const std::string& name;
};

// ret
struct ir_ret {
};

// mov
struct ir_load {
    u64 src;
    u64 dest;
    BuiltinKind type;
};

struct ir_store {
    u64 src;
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
// rol - rotate left <<<
// ror - rotate right >>>
// rcl - rotate carry left @<<
// rcr - rotate carry right @>>
// shl - shift left, unsigned multiply <<
// shr - shift right, unsigned divide >>
// sal - shift left, signed multiply <<
// sar - shift right, signed divide <<
// clc - clear carry flag

// push - push bytes to the stack
// pop - pop values from the stack

// load i32, dest, src
// load i32, $1, $0

// how do we want to use mmx instructions?
// should we leave that to the optimizer? or allow their use in the IR

struct ir_opcode {
    ir_opcode_id opcodeId;

    union {
        ir_nop nop;

        ir_label label;

        ir_jo jo;
        ir_jno jno;

        ir_jb jb;
        ir_jnb jnb;
    };

    ir_opcode()
    { }

    ~ir_opcode()
    { }

    ir_opcode(ir_nop nop) :
        opcodeId(ir_opcode_id::NOP),
        nop(nop)
    { }

    ir_opcode(ir_label label) :
        opcodeId(ir_opcode_id::Label),
        label(label)
    { }
};

constexpr int OPCODE_SIZE = sizeof(ir_opcode);

std::ostream& operator <<(std::ostream& out, const ir_opcode& opcode);

} // namespace vc

#endif // VC_IR_OPCODE_H_INCLUDE
