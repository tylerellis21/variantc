#ifndef OPGEN_H_INCLUDE
#define OPGEN_H_INCLUDE

#include <vc/ast/df_ast_visitor.h>
#include <vc/opcode.h>
#include <t/struct/map.h>

namespace t {
namespace vc {

// Maps variables to their assigned index 
// We store the variable name in long form
// to avoid any duplicate names in namespaces 
// and scoping issues.
typedef Map<Name, u16> VariableMap;

struct OPGenFunction {
    // Name of the generated function.
    Name* name;
    u16 local_index;
    List<Opcode> opcodes;
    VariableMap local_map;
    
    inline OPGenFunction(Name* name) :
        name(name),
        local_index(0),
        opcodes(List<Opcode>(256)),
        local_map(VariableMap())
    { }
};

inline bool is_local_declaration(VarDecl* var_decl) {
    
    t_assert(var_decl);      

    // If the declarations parent is a module or a namespace we 
    // know we have a module level declaration.
    if (var_decl->parent->kind == DeclKind::ModuleDecl ||
        var_decl->parent->kind == DeclKind::NamespaceDecl) return false;
    
    return true;
}

// Generate the stack based vm opcodes.
struct OPGen : DFAstVisitor {

    // Used to keep track of the current function being generated
    // along with the needed data.
    Stack<OPGenFunction*> function_stack;
    List<OPGenFunction*> functions;
    
    // Map of the global variable indexs.
    u16 global_index;
    VariableMap global_map;

    inline OPGen() :
        function_stack(Stack<OPGenFunction*>(256)),
        functions(List<OPGenFunction*>(256)),
        global_index(0),
        global_map(VariableMap())
    { }

    ~OPGen() { }

    inline void generate(Decl* decl) {
        dispatch(decl);
    }
    
    bool traverse_ModuleDecl(ModuleDecl* module_decl) override;
    bool traverse_FunctionDecl(FunctionDecl* function_decl) override;
    bool traverse_VarDecl(VarDecl* var_decl) override;
    
    bool visit_VarDecl(VarDecl* var_decl) override;
    bool visit_ReturnStmt(ReturnStmt* stmt) override;
    bool visit_IntegerLiteral(IntegerLiteral* value) override;
    
    bool visit_BinaryOpExpr(BinaryOpExpr* binary_op_expr) override;
    bool visit_DeclRefExpr(DeclRefExpr* decl_ref_expr) override;
};

} // namespace vc
} // namespace t

#endif // OPGEN_H_INCLUDE
