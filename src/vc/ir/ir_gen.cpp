#include <vc/ir/ir_gen.h>
#include <vc/ast/decl.h>
#include <vc/ast/stmt.h>
#include <vc/ast/expr.h>
#include <vc/ast/type.h>

namespace vc {

void IRGen::generate(Decl* decl) {
    switch (decl->declKind) {
        default:
        // something something unhandled declaration kind in ir generation
        break;
    }
}

void IRGen::generate(Stmt* stmt) {
    switch (stmt->stmtKind) {
        default:
        // something something unhandled statement kind in ir generation
        break;
    }
}

void IRGen::generate(Expr* expr) {
    switch (expr->exprKind) {
        default:
        // something something unhandled expression kind in ir generation
        break;
    }
}

void IRGen::generate(Type* type) {
    switch (type->typeKind) {
        default:
        // something something unhandled type kind in ir generation
        break;
    }
}
}