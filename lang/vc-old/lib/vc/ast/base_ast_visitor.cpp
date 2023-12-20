#include <vc/ast/base_ast_visitor.h>

namespace t {
namespace vc {

bool BaseAstVisitor::dispatch(Decl* decl) {

    if (!decl) return true;

    bool result = false;

    decl_stack.push(decl);

    if (!visit_Decl(decl)) {
        decl_stack.pop();
        return false;
    }

    switch (decl->kind) {
    #define DEFINE(BASE, CLASS) case DeclKind::CLASS: result = traverse_##CLASS(static_cast<CLASS*>(decl)); break;
    #include <vc/definitions/decls.def>
    #undef DEFINE
    } // switch (decl->kind)

    decl_stack.pop();

    return result;
}

bool BaseAstVisitor::dispatch(Stmt* stmt) {

    if (!stmt) return true;

    if (stmt->stmt_kind == StmtKind::ExprStmt) {
        return dispatch(static_cast<Expr*>(stmt));
    }

    bool result = false;

    stmt_stack.push(stmt);

    if (!visit_Stmt(stmt)) {
        stmt_stack.pop();
        return false;
    }


    switch (stmt->stmt_kind) {
    #define DEFINE(BASE, CLASS) case StmtKind::CLASS: result = traverse_##CLASS(static_cast<CLASS*>(stmt)); break;
    #include <vc/definitions/stmts.def>
    #undef DEFINE
    } // switch (stmt->stmt_kind)

    stmt_stack.pop();

    return result;
}

bool BaseAstVisitor::dispatch(Expr* expr) {

    if (!expr) return true;

    bool result = false;

    expr_stack.push(expr);

    if (!visit_Expr(expr)) {
        expr_stack.pop();
        return false;
    }

    switch (expr->expr_kind) {
    #define DEFINE(BASE, CLASS) case ExprKind::CLASS: result = traverse_##CLASS(static_cast<CLASS*>(expr)); break;
    #include <vc/definitions/exprs.def>
    #undef DEFINE
    } // switch (expr->expr_kind)

    expr_stack.pop();

    return result;
}

bool BaseAstVisitor::dispatch(Type* type) {

    if (!type) return true;

    RIFN(visit_Type(type));

    switch (type->kind) {
    #define DEFINE(BASE, CLASS) case TypeKind::CLASS: return traverse_##CLASS(static_cast<CLASS*>(type));
    #include <vc/definitions/types.def>
    #undef DEFINE
    } // switch (type->kind)

    return false;
}

} // namespace vc
} // namespace t
