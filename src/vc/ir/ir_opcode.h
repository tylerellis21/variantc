#ifndef VC_IR_OPCODE_H_INCLUDE
#define VC_IR_OPCODE_H_INCLUDE

#include <string>
#include <vector>
#include <vc/types.h>
#include <vc/basic/builtinkind.h>
#include <unordered_map>
#include <vc/ir/ir_type.h>

namespace vc {

enum class ir_opcode_id {
    NOP = 0,
    Label = 1,
    CALL,
    RET,
    ALLOC,
    DEALLOC,
    LOAD,
    LOAD_REF,
    STORE,
    STORE_REF,
    STORE_CONST,
    CMP,
    JUMP,
    BINOP,
    UNARYOP,
    PHI
};

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

struct ir_ssa_value {
    u64 index;
    ir_type* type;

    ir_ssa_value(u64 index, ir_type* type)
        : index(index), type(type) {}
};

struct ir_opcode {
    ir_opcode_id opcode_id;

    ir_opcode(ir_opcode_id id)
        : opcode_id(id) {}

    virtual ~ir_opcode() = default;
};

struct ir_nop : public ir_opcode {
    ir_nop() : ir_opcode(ir_opcode_id::NOP) {}
};

struct ir_label : public ir_opcode {
    std::string name;

    ir_label(const std::string& name)
        : ir_opcode(ir_opcode_id::Label), name(name) {}
};

struct ir_call : public ir_opcode {
    std::string name;
    std::vector<ir_ssa_value> args;

    ir_call(const std::string& name, const std::vector<ir_ssa_value>& args)
        : ir_opcode(ir_opcode_id::CALL), name(name), args(args) {}
};

// should we return include a ir_type like in clang?
struct ir_ret : public ir_opcode {
    ir_ret() : ir_opcode(ir_opcode_id::RET) {}
};

struct ir_alloc : public ir_opcode {
    ir_ssa_value value;

    ir_alloc(ir_ssa_value value)
        : ir_opcode(ir_opcode_id::ALLOC), value(value) {}
};

struct ir_dealloc : public ir_opcode {
    ir_ssa_value value;

    ir_dealloc(ir_ssa_value value)
        : ir_opcode(ir_opcode_id::DEALLOC), value(value) {}
};

struct ir_load : public ir_opcode {
    ir_ssa_value src;
    ir_ssa_value dest;

    ir_load(ir_ssa_value dest, ir_ssa_value src)
        : ir_opcode(ir_opcode_id::LOAD),
            type(type),
            dest(dest),
            src(src) {}
};

struct ir_load_ref : public ir_opcode {
    ir_ssa_value src;
    ir_ssa_value dest;

    ir_load_ref(ir_ssa_value dest, ir_ssa_value src)
        : ir_opcode(ir_opcode_id::LOAD_REF), dest(dest), src(src) {}
};

struct ir_store : public ir_opcode {
    ir_ssa_value src;
    ir_ssa_value dest;

    ir_store(ir_ssa_value dest, ir_ssa_value src)
        : ir_opcode(ir_opcode_id::STORE), dest(dest), src(src) {}
};

struct ir_store_ref : public ir_opcode {
    ir_ssa_value src;
    ir_ssa_value dest;

    ir_store_ref(ir_ssa_value dest, ir_ssa_value src)
        : ir_opcode(ir_opcode_id::STORE_REF), dest(dest), src(src) {}
};

struct ir_store_const : public ir_opcode {
    union {
        i64 value_i64;
        u64 value_u64;
    };
    ir_ssa_value dest;

    ir_store_const(ir_ssa_value dest, u64 value)
        : ir_opcode(ir_opcode_id::STORE_CONST), dest(dest), value_u64(value) {}

    ir_store_const(ir_ssa_value dest, i64 value)
        : ir_opcode(ir_opcode_id::STORE_CONST), dest(dest), value_i64(value) {}
};

struct ir_cmp : public ir_opcode {
    ir_ssa_value dest;
    ir_ssa_value lhs;
    ir_ssa_value rhs;

    ir_cmp(ir_ssa_value dest, ir_ssa_value lhs, ir_ssa_value rhs)
        : ir_opcode(ir_opcode_id::CMP), dest(dest), lhs(lhs), rhs(rhs) {}
};

struct ir_jump : public ir_opcode {
    ir_jump_type jump_type;
    std::string target;

    ir_jump(ir_jump_type jump_type, const std::string& target)
        : ir_opcode(ir_opcode_id::JUMP), jump_type(jump_type), target(target) {}
};

struct ir_binop : public ir_opcode {
    ir_binop_type op_type;
    ir_ssa_value dest;
    ir_ssa_value lhs;
    ir_ssa_value rhs;

    ir_binop(ir_binop_type op_type, ir_ssa_value dest, ir_ssa_value lhs, ir_ssa_value rhs)
        : ir_opcode(ir_opcode_id::BINOP), op_type(op_type), dest(dest), lhs(lhs), rhs(rhs) {}
};

struct ir_unaryop : public ir_opcode {
    ir_unaryop_type op_type;
    ir_ssa_value dest;
    ir_ssa_value src;

    ir_unaryop(ir_unaryop_type op_type, ir_ssa_value dest, ir_ssa_value src)
        : ir_opcode(ir_opcode_id::UNARYOP), op_type(op_type), dest(dest), src(src) {}
};

// PHI node for SSA representation
struct ir_phi : public ir_opcode {
    ir_ssa_value dest;
    std::vector<std::pair<ir_ssa_value, ir_string>> sources; // (value, label)

    ir_phi(ir_ssa_value dest, const std::vector<std::pair<ir_ssa_value, ir_string>>& sources)
        : ir_opcode(ir_opcode_id::PHI), dest(dest), sources(sources) {}
};

using ir_opcode_list = std::vector<ir_opcode*>;

constexpr int IR_OPCODE_SIZE = sizeof(ir_opcode);

std::ostream& operator <<(std::ostream& out, const ir_opcode& opcode);

struct ir_module {
    std::string name;
    std::vector<ir_ssa_value> globals;
    std::vector<ir_function> functions;
    ir_string_table string_table;
};

struct ir_function {
    std::string name;
    std::vector<ir_ssa_value> args;
    std::vector<ir_opcode> opcodes;
};

struct ir_struct {
    std::string name;
    std::vector<ir_ssa_value> basic_fields;
    std::vector<ir_struct> struct_fields;
};

} // namespace vc

#endif // VC_IR_OPCODE_H_INCLUDE