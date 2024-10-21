#ifndef VC_IR_GEN_H_INCLUDE
#define VC_IR_GEN_H_INCLUDE

#include <vc/ir/ir_opcode.h>

namespace vc {

struct ModuleDecl;
struct Decl;
struct DeclGroup;
struct Stmt;
struct Expr;
struct Type;

struct IRGenContext {
    u64 current_ssa_index = 0; // Start counting from 0 for each function
    // Other function-specific state (e.g., variable-to-SSA mappings)

    // You could also maintain a mapping of variable names to SSA values
    std::unordered_map<std::string, ir_ssa_value> var_ssa_map;
};

struct IRGen {
    ir_module current_module;
    ir_module generateModule(ModuleDecl* decl);
    void generateDeclGroup(DeclGroup* declGroup);
    void generateDecl(Decl* decl);
    void generateStmt(Stmt* stmt);
    void generateExpr(Expr* expr);
    void generateType(Type* type);
};

} // namespace vc

#endif // VC_IR_GEN_H_INCLUDE