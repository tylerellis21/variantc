#ifndef VC_IR_GEN_H_INCLUDE
#define VC_IR_GEN_H_INCLUDE

namespace vc {

struct Decl;
struct DeclGroup;
struct Stmt;
struct Expr;
struct Type;

struct IRGen {
    void generateDeclGroup(DeclGroup* declGroup);
    void generateDecl(Decl* decl);
    void generateStmt(Stmt* stmt);
    void generateExpr(Expr* expr);
    void generateType(Type* type);
};


} // namespace vc

#endif // VC_IR_GEN_H_INCLUDE