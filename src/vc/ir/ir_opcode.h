#ifndef VC_IR_OPCODE_H_INCLUDE
#define VC_IR_OPCODE_H_INCLUDE

#include <string>
#include <vector>
#include <vc/types.h>
#include <vc/basic/builtinkind.h>

namespace vc {


struct ir_string {
    u64 index;
    char* ptr;
};

struct ir_string_table {
    std::vector<ir_string> strings;
};

enum class ir_binop_type {
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    OR,
    AND,
    XOR,
    ROL,
    ROR,
    RCL,
    RCR,
    SHL,
    SHR,
    SAL,
    SAR,
};

enum class ir_unaryop_type {
    INC,
    DEC,
    NOT,
};

// Enum for different jump types
enum class ir_jump_type {
    JO,     // Jump if overflow
    JNO,    // Jump if not overflow

    JB,     // Jump if below
    JNB,    // Jump if not below

    JZ,     // Jump if zero
    JNZ,    // Jump if not zero

    JBE,    // Jump if below or equal
    JNBE,   // Jump if not below or equal

    JS,     // Jump if sign
    JNS,    // Jump if not sign

    JP,     // Jump if parity
    JNP,    // Jump if not parity

    JL,     // Jump if less
    JNL,    // Jump if not less
    JLE,    // Jump if less or equal
    JNLE,   // Jump if not less or equal

    JG,     // Jump if greater
    JNG,    // Jump if not greater
    JGE,    // Jump if greater or equal
    JNGE,   // Jump if not greater or equal

    UNCONDITIONAL // For unconditional jumps
};

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
    JUMP,
    BINOP,
    UNARYOP,
    PHI
};

// SSA value structure to represent values and types
struct ir_ssa_value {
    u64 index;
    BuiltinKind type;

    ir_ssa_value(u64 index, BuiltinKind type) : index(index), type(type) {}
};

// Phi node structure for SSA
struct ir_phi {
    ir_ssa_value result;
    ir_ssa_value lhs;
    ir_ssa_value rhs;

    // Constructor
    ir_phi(ir_ssa_value result, ir_ssa_value lhs, ir_ssa_value rhs)
        : result(result), lhs(lhs), rhs(rhs) {}

    // Default constructor and destructor
    ir_phi() = default;
    ~ir_phi() = default;

    // Copy and move constructors
    ir_phi(const ir_phi& other) = default;
    ir_phi& operator=(const ir_phi& other) = default;
    ir_phi(ir_phi&& other) noexcept = default;
    ir_phi& operator=(ir_phi&& other) noexcept = default;
};

struct ir_label {
    ir_string name;
    ir_label(ir_string name) : name(name) {}
};

struct ir_nop {};

struct ir_jump {
    ir_jump_type jump_type;
    std::string target;

    ir_jump(ir_jump_type jump_type, const std::string& target)
        : jump_type(jump_type), target(target) {}
};

struct ir_binop {
    ir_binop_type op_type;
    ir_ssa_value lhs;
    ir_ssa_value rhs;
    ir_ssa_value dest;

    ir_binop(ir_binop_type op_type, ir_ssa_value lhs, ir_ssa_value rhs, ir_ssa_value dest)
        : op_type(op_type), lhs(lhs), rhs(rhs), dest(dest) {}
};

struct ir_unaryop {
    ir_unaryop_type op_type;
    ir_ssa_value src;
    ir_ssa_value dest;

    ir_unaryop(ir_unaryop_type op_type, ir_ssa_value src, ir_ssa_value dest)
        : op_type(op_type), src(src), dest(dest) {}
};

struct ir_call {
    ir_string name;
    ir_call(ir_string name) : name(name) {}
};

struct ir_ret {};

// Allocation structure
enum class ir_alloc_type {
    Stack,
    Heap
};

struct ir_alloc {
    ir_ssa_value value;
    ir_alloc_type alloc_type;

    ir_alloc(ir_ssa_value value, ir_alloc_type alloc_type)
        : value(value), alloc_type(alloc_type) {}
};

struct ir_dealloc {
    ir_ssa_value value;

    ir_dealloc(ir_ssa_value value)
        : value(value) { }
};

// Load and store structures
struct ir_load {
    ir_ssa_value src;
    ir_ssa_value dest;

    ir_load(ir_ssa_value dest, ir_ssa_value src)
        : dest(dest), src(src) {}
};

struct ir_store {
    ir_ssa_value src;
    ir_ssa_value dest;

    ir_store(ir_ssa_value dest, ir_ssa_value src)
        : dest(dest), src(src) {}
};

struct ir_store_const {
    union {
        i64 value_i64;
        u64 value_u64;
    };
    ir_ssa_value dest;

    ir_store_const(ir_ssa_value dest, u64 value)
        : dest(dest), value_u64(value) {}

    ir_store_const(ir_ssa_value dest, i64 value)
        : dest(dest), value_i64(value) {}
};

// Comparison structure
struct ir_cmp {
    ir_ssa_value dest;
    ir_ssa_value lhs;
    ir_ssa_value rhs;

    ir_cmp(ir_ssa_value dest, ir_ssa_value lhs, ir_ssa_value rhs)
        : dest(dest), lhs(lhs), rhs(rhs) {}
};

// Opcode structure
struct ir_opcode {
    ir_opcode_id opcodeId;
    union {
        ir_nop nop;
        ir_label label;
        ir_call call;
        ir_ret ret;
        ir_alloc alloc;
        ir_dealloc dealloc;
        ir_load load;
        ir_store store;
        ir_store_const store_const;
        ir_cmp cmp;
        ir_jump jump;
        ir_binop binop;
        ir_unaryop unaryop;
        ir_phi phi;
    };

    ir_opcode() {}
    ~ir_opcode() {}

    ir_opcode(ir_nop nop) : opcodeId(ir_opcode_id::NOP), nop(nop) {}
    ir_opcode(ir_label label) : opcodeId(ir_opcode_id::Label), label(label) {}
    ir_opcode(ir_call call) : opcodeId(ir_opcode_id::CALL), call(call) {}
    ir_opcode(ir_load load) : opcodeId(ir_opcode_id::LOAD), load(load) {}
    ir_opcode(ir_store store) : opcodeId(ir_opcode_id::STORE), store(store) {}
    ir_opcode(ir_store_const store_const) : opcodeId(ir_opcode_id::STORE_CONST), store_const(store_const) {}
    ir_opcode(ir_cmp cmp) : opcodeId(ir_opcode_id::CMP), cmp(cmp) {}
    ir_opcode(ir_ret ret) : opcodeId(ir_opcode_id::RET), ret(ret) {}
    ir_opcode(ir_alloc alloc) : opcodeId(ir_opcode_id::ALLOC), alloc(alloc) {}
    ir_opcode(ir_dealloc dealloc) : opcodeId(ir_opcode_id::DEALLOC), dealloc(dealloc) {}
    ir_opcode(ir_jump jump) : opcodeId(ir_opcode_id::JUMP), jump(jump) {}
    ir_opcode(ir_binop binop) : opcodeId(ir_opcode_id::BINOP), binop(binop) {}
    ir_opcode(ir_unaryop unaryop) : opcodeId(ir_opcode_id::UNARYOP), unaryop(unaryop) {}
    ir_opcode(ir_phi phi) : opcodeId(ir_opcode_id::PHI), phi(phi) {}
};

constexpr int IR_OPCODE_SIZE = sizeof(ir_opcode);

std::ostream& operator <<(std::ostream& out, const ir_opcode& opcode);

} // namespace vc

#endif // VC_IR_OPCODE_H_INCLUDE