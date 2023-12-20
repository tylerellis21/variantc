#ifndef VC_IR_OPCODE_H_INCLUDE
#define VC_IR_OPCODE_H_INCLUDE

#include <string>

#include <vc/types.h>
#include <vc/basic/builtinkind.h>

namespace vc {

enum class ir_opcode_id {
    NOP = 0,
    Label = 1,

    CALL,
    RET,

    ALLOC,
    DEALLOC,

    LOAD,
    STORE,
    STORE_CONST,

    CMP,

    JO,
    JNO,

    JB,
    JNB,

    JZ,
    JNZ,

    JBE,
    JNBE,

    JS,
    JNS,

    JP,
    JNP,

    JL,
    JNL,
    JLE,
    JNLE,

    JG,
    JGE,
    JNG,
    JNGE,

    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    INC,
    DEC,

    OR,
    AND,
    XOR,
    NOT,

    ROL,
    ROR,

    RCL,
    RCR,

    SHL,
    SHR,

    SAL,
    SAR,
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

// jg - jump if less
struct ir_jg {
    const std::string& name;

    ir_jg(const std::string& name) :
        name(name)
    { }
};

// jge - jump if less
struct ir_jge {
    const std::string& name;

    ir_jge(const std::string& name) :
        name(name)
    { }
};

// jng - jump if less
struct ir_jng {
    const std::string& name;

    ir_jng(const std::string& name) :
        name(name)
    { }
};


// jnge - jump if less
struct ir_jnge {
    const std::string& name;

    ir_jnge(const std::string& name) :
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

enum class ir_alloc_type {
    Stack,
    Heap
};

struct ir_alloc {
    u64 index;
    BuiltinKind type;
    ir_alloc_type alloc_type;

    ir_alloc(u64 index, BuiltinKind type, ir_alloc_type alloc_type) :
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

struct ir_store_const {

    union {
        i64 value_i64;
        u64 value_u64;
    };

    u64 dest;
    BuiltinKind type;

    ir_store_const(u64 dest, u64 value, BuiltinKind type) :
        dest(dest),
        value_u64(value),
        type(type)
    { }

    ir_store_const(u64 dest, i64 value, BuiltinKind type) :
        dest(dest),
        value_i64(value),
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

// mod
struct ir_mod {
    u64 lhs;
    u64 rhs;
    u64 dest;
    BuiltinKind type;

    ir_mod(u64 lhs, u64 rhs, u64 dest, BuiltinKind type) :
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

        ir_call call;
        ir_ret ret;
        ir_alloc alloc;
        ir_load load;
        ir_store store;
        ir_store_const store_const;
        ir_cmp cmp;

        ir_jo jo;
        ir_jno jno;
        ir_jb jb;
        ir_jnb jnb;
        ir_jz jz;
        ir_jnz jnz;
        ir_jbe jbe;
        ir_jnbe jnbe;
        ir_js js;
        ir_jns jns;
        ir_jp jp;
        ir_jnp jnp;
        ir_jl jl;
        ir_jnl jnl;
        ir_jle jle;
        ir_jnle jnle;
        ir_jg jg;
        ir_jge jge;
        ir_jng jng;
        ir_jnge jnge;

        ir_add add;
        ir_sub sub;
        ir_div div;
        ir_mul mul;
        ir_mod mod;
        ir_inc inc;
        ir_dec dec;

        ir_or or;
        ir_and and;
        ir_xor xor;
        ir_not not;

        ir_rol rol;
        ir_ror ror;

        ir_rcl rcl;
        ir_rcr rcr;
        ir_shl shl;
        ir_shr shr;
        ir_sal sal;
        ir_sar sar;
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

    ir_opcode(ir_call call) :
        opcodeId(ir_opcode_id::CALL),
        call(call)
    { }

    ir_opcode(ir_load load) :
        opcodeId(ir_opcode_id::LOAD),
        load(load)
    { }

    ir_opcode(ir_store store) :
        opcodeId(ir_opcode_id::STORE),
        store(store)
    { }

    ir_opcode(ir_store_const store_const) :
        opcodeId(ir_opcode_id::STORE_CONST),
        store_const(store_const)
    { }

    ir_opcode(ir_cmp cmp) :
        opcodeId(ir_opcode_id::CMP),
        cmp(cmp)
    { }

    ir_opcode(ir_ret ret) :
        opcodeId(ir_opcode_id::RET),
        ret(ret)
    { }

    ir_opcode(ir_alloc alloc) :
        opcodeId(ir_opcode_id::ALLOC),
        alloc(alloc)
    { }

    ir_opcode(ir_jo jo) :
        opcodeId(ir_opcode_id::JO),
        jo(jo)
    { }

    ir_opcode(ir_jno jno) :
        opcodeId(ir_opcode_id::JNO),
        jo(jo)
    { }

    ir_opcode(ir_jb jb) :
        opcodeId(ir_opcode_id::JB),
        jb(jb)
    { }

    ir_opcode(ir_jnb jnb) :
        opcodeId(ir_opcode_id::JNB),
        jnb(jnb)
    { }

    ir_opcode(ir_jz jz) :
        opcodeId(ir_opcode_id::JZ),
        jz(jz)
    { }

    ir_opcode(ir_jnz jnz) :
        opcodeId(ir_opcode_id::JNZ),
        jnz(jnz)
    { }

    ir_opcode(ir_jbe jbe) :
        opcodeId(ir_opcode_id::JBE),
        jbe(jbe)
    { }

    ir_opcode(ir_jnbe jnbe) :
        opcodeId(ir_opcode_id::JNBE),
        jnbe(jnbe)
    { }

    ir_opcode(ir_js js) :
        opcodeId(ir_opcode_id::JS),
        js(js)
    { }

    ir_opcode(ir_jns jns) :
        opcodeId(ir_opcode_id::JNS),
        jns(jns)
    { }

    ir_opcode(ir_jp jp) :
        opcodeId(ir_opcode_id::JP),
        jp(jp)
    { }

    ir_opcode(ir_jnp jnp) :
        opcodeId(ir_opcode_id::JNP),
        jnp(jnp)
    { }

    ir_opcode(ir_jl jl) :
        opcodeId(ir_opcode_id::JL),
        jl(jl)
    { }

    ir_opcode(ir_jnl jnl) :
        opcodeId(ir_opcode_id::JNL),
        jnl(jnl)
    { }

    ir_opcode(ir_jle jle) :
        opcodeId(ir_opcode_id::JLE),
        jle(jle)
    { }

    ir_opcode(ir_jnle jnle) :
        opcodeId(ir_opcode_id::JNLE),
        jnle(jnle)
    { }

    ir_opcode(ir_jg jg) :
        opcodeId(ir_opcode_id::JG),
        jg(jg)
    { }

    ir_opcode(ir_jge jge) :
        opcodeId(ir_opcode_id::JGE),
        jge(jge)
    { }

    ir_opcode(ir_jng jng) :
        opcodeId(ir_opcode_id::JNG),
        jng(jng)
    { }

    ir_opcode(ir_jnge jnge) :
        opcodeId(ir_opcode_id::JNGE),
        jnge(jnge)
    { }

    ir_opcode(ir_add add) :
        opcodeId(ir_opcode_id::ADD),
        add(add)
    { }

    ir_opcode(ir_sub sub) :
        opcodeId(ir_opcode_id::SUB),
        sub(sub)
    { }

    ir_opcode(ir_mul mul) :
        opcodeId(ir_opcode_id::MUL),
        mul(mul)
    { }

    ir_opcode(ir_div div) :
        opcodeId(ir_opcode_id::DIV),
        div(div)
    { }

    ir_opcode(ir_mod mod) :
        opcodeId(ir_opcode_id::MOD),
        mod(mod)
    { }

    ir_opcode(ir_inc inc) :
        opcodeId(ir_opcode_id::INC),
        inc(inc)
    { }

    ir_opcode(ir_dec dec) :
        opcodeId(ir_opcode_id::DEC),
        dec(dec)
    { }

    ir_opcode(ir_or or) :
        opcodeId(ir_opcode_id::OR),
        or(or)
    { }

    ir_opcode(ir_and and) :
        opcodeId(ir_opcode_id::AND),
        and(and)
    { }

    ir_opcode(ir_xor xor) :
        opcodeId(ir_opcode_id::XOR),
        xor(xor)
    { }


    /*


    XOR,
    NOT,

    ROL,
    ROR,

    RCL,
    RCR,

    SHL,
    SHR,

    SAL,
    SAR,
    */
};

constexpr int OPCODE_SIZE = sizeof(ir_opcode);

std::ostream& operator <<(std::ostream& out, const ir_opcode& opcode);

} // namespace vc

#endif // VC_IR_OPCODE_H_INCLUDE
