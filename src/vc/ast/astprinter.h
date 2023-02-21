#ifndef VC_AST_PRINTER_H_INCLUDE
#define VC_AST_PRINTER_H_INCLUDE

#include <vc/types.h>

namespace vc {

struct Decl;
struct DeclGroup;
struct Stmt;
struct Expr;
struct Type;

void printDecl(Decl* decl, i32 indent);
void printDeclGroup(DeclGroup* declGroup, i32 indent);
void printStmt(Stmt* stmt, i32 indent);
void printExpr(Expr* expr, i32 indent);
void printType(Type* type);

} // namespace vc

#endif // VC_AST_PRINTER_H_INCLUDE