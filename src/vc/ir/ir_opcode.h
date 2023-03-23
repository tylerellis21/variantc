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

    ir_jb(const std::string& name) :
        name(name)
    { }
};

// jnb - jump if not below
struct ir_jnb {
    const std::string& name;

    ir_jnb(const std::string& name) :
        name(name)
    { }
};

// jz - jump if zero
struct ir_jz {
    const std::string& name;

    ir_jz(const std::string& name) :
        name(name)
    { }
};

// jnz - jump if not zero
struct ir_jnz {
    const std::string& name;

    ir_jnz(const std::string& name) :
        name(name)
    { }
};

// jbe - jump if below or equal
struct ir_jbe {
    const std::string& name;

    ir_jbe(const std::string& name) :
        name(name)
    { }
};

// jnbe - jump if not below or equal
struct ir_jnbe {
    const std::string& name;

    ir_jnbe(const std::string& name) :
        name(name)
    { }
};

// js - jump if sign
struct ir_js {
    const std::string& name;

    ir_js(const std::string& name) :
        name(name)
    { }
};

// jns - jump if not sign
struct ir_jns {
    const std::string& name;

    ir_jns(const std::string& name) :
        name(name)
    { }
};

// jp - jump if parity
struct ir_jp {
    const std::string& name;

    ir_jp(const std::string& name) :
        name(name)
    { }
};

// jnp - jump if not parity
struct ir_jnp {
    const std::string& name;
    ir_jnp(const std::string& name) :
        name(name)
    { }
};

// jl - jump if less
struct ir_jl {
    const std::string& name;

    ir_jl(const std::string& name) :
        name(name)
    { }
};

// jnl - jump if not less
struct ir_jnl {
    const std::string& name;

    ir_jnl(const std::string& name) :
        name(name)
    { }
};

// jle - jump if less or equal
struct ir_jle {
    const std::string& name;

    ir_jle(const std::string& name) :
        name(name)
    { }
};

// jnle - jump if not less or equal
struct ir_jnle {
    const std::string& name;

    ir_jnle(const std::string& name) :
        name(name)
    { }
};

struct ir_call {
    const std::string& name;

    ir_call(const std::string& name) :
        name(name)
    { }
};

struct ir_ret {
};

struct ir_alloc {
    u64 index;
    BuiltinKind type;

    ir_alloc(u64 index, BuiltinKind type) :
        index(index),
        type(type)
    { }
};

struct ir_load {
    u64 src;
    u64 dest;
    BuiltinKind type;

    ir_load(u64 dest, u64 src, BuiltinKind type) :
        dest(dest),
        src(src),
        type(type)
    { }
};

struct ir_store {
    u64 src;
    u64 dest;
    BuiltinKind type;

    ir_store(u64 dest, u64 src, BuiltinKind type) :
        dest(dest),
        src(src),
        type(type)
    { }
};

// cmp - compare two operands
struct ir_cmp {
    u64 lhs;
    u64 rhs;
    BuiltinKind type;

    ir_cmp(u64 lhs, u64 rhs, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        type(type)
    { }
};

// add - add
struct ir_add {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_add(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// adc - add with carry
struct ir_adc {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_adc(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// sub - subtract
struct ir_sub {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_sub(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// sbb - subtract with borrow
struct ir_sbb {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_sbb(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// mul - multiply
struct ir_mul {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_mul(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// div - divide
struct ir_div {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_div(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// inc - add 1
struct ir_inc {
    u64 lhs;
    u64 dest;
    BuiltinKind type;

    ir_inc(u64 lhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        dest(dest),
        type(type)
    { }
};

// dec - subtract 1
struct ir_dec {
    u64 lhs;
    u64 dest;
    BuiltinKind type;

    ir_dec(u64 lhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        dest(dest),
        type(type)
    { }
};

// or - logical inclusive OR
struct ir_or {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_or(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// and - logical AND
struct ir_and {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_and(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// xor - logical exclusive OR
struct ir_xor {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_xor(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// not - one's complement negation
struct ir_not {
    u64 lhs;
    u64 dest;
    BuiltinKind type;

    ir_not(u64 lhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        dest(dest),
        type(type)
    { }
};

// neg - two's complement negation
struct ir_neg {
    u64 lhs;
    u64 dest;
    BuiltinKind type;

    ir_neg(u64 lhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        dest(dest),
        type(type)
    { }
};

// rol - rotate left <<<
struct ir_rol {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_rol(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// ror - rotate right >>>
struct ir_ror {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_ror(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// rcl - rotate carry left @<<
struct ir_rcl {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_rcl(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// rcr - rotate carry right @>>
struct ir_rcr {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_rcr(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// shl - shift left, unsigned multiply <<
struct ir_shl {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_shl(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// shr - shift right, unsigned divide >>
struct ir_shr {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_shr(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// sal - shift left, signed multiply <<
struct ir_sal {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_sal(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

// sar - shift right, signed divide <<
struct ir_sar {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_sar(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
        lhs(lhs),
        rhs(rhs),
        dest(dest),
        type(type)
    { }
};

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
