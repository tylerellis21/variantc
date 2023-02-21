#include <vc/ast/astprinter.h>

#include <vc/ast/decl.h>
#include <vc/ast/declgroup.h>
#include <vc/ast/expr.h>
#include <vc/ast/name.h>
#include <vc/ast/stmt.h>
#include <vc/ast/type.h>

namespace vc {

void printDecl(Decl* decl, i32 indent) {
    switch (decl->declKind) {
        default:
        std::cout << "Unhandled decl kind in ast printer" << std::endl;
        break;
    }
}

void printDeclGroup(DeclGroup* declGroup, i32 indent) {
}

void printStmt(Stmt* stmt, i32 indent) {
    switch (stmt->stmtKind) {
        default:
        std::cout << "Unhandled stmt kind in ast printer" << std::endl;
        break;
    }
}

void printExpr(Expr* expr, i32 indent) {
    switch (expr->exprKind) {
        default:
        std::cout << "Unhandled expr kind in ast printer" << std::endl;
        break;
    }
}

void printType(Type* type) {
    switch (type->typeKind) {
        default:
        std::cout << "Unhandled type kind in ast printer" << std::endl;
        break;
    }
}

} // namespace vc