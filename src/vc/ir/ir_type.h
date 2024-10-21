#ifndef VC_IR_TYPE_H_INCLUDE
#define VC_IR_TYPE_H_INCLUDE

#include <vc/types.h>
#include <vc/basic/builtinkind.h>
#include <vc/ast/decl.h>

namespace vc {

struct ir_type {
    virtual ~ir_type() = default;
    virtual std::string get_type_name() const = 0;
};

// Built-in types derived from ir_type
struct ir_builtin_type : public ir_type {
    BuiltinKind kind;

    ir_builtin_type(BuiltinKind kind) : kind(kind) {}

    std::string get_type_name() const override {
        return builtinKindString(kind);
    }
};

struct ir_record_type : public ir_type {
    RecordKind record_kind;
    std::string name;
    std::vector<ir_type*> fields;

    ir_struct_type(RecordKind record_kind, std::string& name, const std::vector<ir_type*>& fields) :
        record_kind(record_kind),
        name(name),
        fields(fields)
    {}

    std::string get_type_name() const override {
        return name;
    }
};

// Function type to represent function signatures
struct ir_function_type : public ir_type {
    std::string name;
    ir_type* return_type;
    std::vector<ir_type*> argument_types;

    ir_function_type(const std::string& name, ir_type* return_type, const std::vector<ir_type*>& argument_types) :
        name(name),
        return_type(return_type),
        argument_types(argument_types)
    {}

    std::string get_type_name() const override {
        return name;
    }
};

} // namespace vc

#endif // VC_IR_TYPE_H_INCLUDE