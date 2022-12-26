#ifndef VC_IR_GEN_H_INCLUDE
#define VC_IR_GEN_H_INCLUDE

namespace vc {

struct Decl;
struct DeclGroup;
struct Stmt;
struct Expr;
struct Type;

struct IRGen {
    void generate(Decl* decl);
    void generate(Stmt* stmt);
    void generate(Expr* expr);
    void generate(Type* type);
};


}

#endif // VC_IR_GEN_H_INCLUDE