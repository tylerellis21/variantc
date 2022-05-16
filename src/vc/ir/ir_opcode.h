#ifndef IR_OPCODE_H_INCLUDE
#define IR_OPCODE_H_INCLUDE

#include <vc/types.h>

namespace vc {

enum ir_opcode_type {
    NOP = 0,
    LABEL = 1
};

struct ir_nop { };

struct ir_label {
    u64 offset;
};


// nop
// flow control

// jo - jump if overflow
// jno - jump if not overflow
// jb - jump if below
// jnb - jump if not below

// jz - jump if zero
// jnz - jump if not zero

// jbe - jump if below or equal
// jnbe - jump if not below or equal

// js - jump if sign
// jns - jump if not sign

// jp - jump if parity
// jnp - jump if not parity

// jl - jump if less
// jnl - jump if not less

// jle - jump if less or equal
// jnle - jump if not less or equal

// call
// ret

// mov
// xchg - exchange register/memory with register

// math

// lea - load effective address

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
// ror - rotate right

// rcl - rotate carry left
// rcr - rotate carry right

// shl - shift left, unsigned multiply
// shr - shift right, unsigned divide

// sal - shift left, signed multiply
// sar - shift right, signed divide

// clc - clear carry flag

// push - push bytes to the stack
// pop - pop values from the stack

// how do we want to use mmx instructions?
// should we leave that to the optimizer? or allow their use in the IR?

struct ir_lea {
    u64 src;
    u64 dest;
    u64 scalar;
};



struct ir_opcode {
    ir_opcode_type type;
    union {
        ir_nop nop;
    };
};

} // namespace vc

#endif // IR_OPCODE_H_INCLUDE
