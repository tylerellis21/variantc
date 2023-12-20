#include <vc/ast/recursive_ast_visitor.h>

namespace t {
namespace vc {

//
// Declarations
//

bool RecursiveAstVisitor::traverse_DeclGroup(DeclGroup* dg) {
    for (Decl* decl : dg->decls) RIFN(dispatch(decl));
    return true;
}

bool RecursiveAstVisitor::traverse_ModuleDecl(ModuleDecl* mod) {
    RIFN(visit_ModuleDecl(mod));
    return traverse_DeclGroup(mod->dg);
}

bool RecursiveAstVisitor::traverse_EnumDecl(EnumDecl* enum_decl) {
    RIFN(visit_EnumDecl(enum_decl));
    return traverse_DeclGroup(enum_decl->dg);
}

bool RecursiveAstVisitor::traverse_EnumConstDecl(EnumConstDecl* enum_const_decl) {
    RIFN(visit_EnumConstDecl(enum_const_decl));
    RIFN(dispatch(enum_const_decl->expr));
    return true;
}

bool RecursiveAstVisitor::traverse_FunctionDecl(FunctionDecl* function_decl) {
    RIFN(visit_FunctionDecl(function_decl));
    for (FunctionArgDecl* arg : function_decl->args) RIFN(dispatch(arg));
    //RIFN(dispatch(function_decl->return_type));
    //RIFN(dispatch(function_decl->template_decl));
    RIFN(dispatch(function_decl->body));
    return true;
}

bool RecursiveAstVisitor::traverse_FunctionArgDecl(FunctionArgDecl* function_arg_decl) {
    RIFN(visit_FunctionArgDecl(function_arg_decl));
    RIFN(dispatch(function_arg_decl->var_decl));
    return true;
}

bool RecursiveAstVisitor::traverse_NamespaceDecl(NamespaceDecl* namespace_decl) {
    RIFN(visit_NamespaceDecl(namespace_decl));
    RIFN(traverse_DeclGroup(namespace_decl->dg));
    return true;
}

bool RecursiveAstVisitor::traverse_RecordDecl(RecordDecl* record_decl) {
    RIFN(visit_RecordDecl(record_decl));
    //RIFN(dispatch(record_decl->template_decl));
    //RIFN(dispatch(record_decl->template_type));
    RIFN(traverse_DeclGroup(record_decl->dg));
    return true;
}

bool RecursiveAstVisitor::traverse_VarDecl(VarDecl* var_decl) {
    RIFN(visit_VarDecl(var_decl));
    //RIFN(dispatch(var_decl->type));
    RIFN(dispatch(var_decl->assignment));
    return true;
}

//
// Statements
//

bool RecursiveAstVisitor::traverse_CaseStmt(CaseStmt* case_stmt) {
    RIFN(visit_CaseStmt(case_stmt));
    RIFN(dispatch(case_stmt->value));
    RIFN(dispatch(case_stmt->stmt));
    return true;
}

bool RecursiveAstVisitor::traverse_CompoundStmt(CompoundStmt* compound_stmt) {
    RIFN(visit_CompoundStmt(compound_stmt));
    for (Stmt* sub_stmt : compound_stmt->statements) RIFN(dispatch(sub_stmt));
    return true;
}

bool RecursiveAstVisitor::traverse_ExprStmt(Stmt* stmt) {
    Expr* expr = static_cast<Expr*>(stmt);
    RIFN(dispatch(expr));
    return true;
}

bool RecursiveAstVisitor::traverse_DeclStmt(DeclStmt* decl_stmt) {
    RIFN(visit_DeclStmt(decl_stmt));
    RIFN(traverse_DeclGroup(decl_stmt->dg));
    return true;
}

bool RecursiveAstVisitor::traverse_DefaultStmt(DefaultStmt* default_stmt) {
    RIFN(visit_DefaultStmt(default_stmt));
    RIFN(dispatch(default_stmt->stmt));
    return true;
}

bool RecursiveAstVisitor::traverse_DoStmt(DoStmt* do_stmt) {
    RIFN(visit_DoStmt(do_stmt));
    RIFN(dispatch(do_stmt->body));
    RIFN(dispatch(do_stmt->while_stmt));
    return true;
}

bool RecursiveAstVisitor::traverse_IfStmt(IfStmt* if_stmt) {
    RIFN(visit_IfStmt(if_stmt));
    RIFN(dispatch(if_stmt->condition));
    RIFN(dispatch(if_stmt->body));
    RIFN(dispatch(if_stmt->else_stmt));
    return true;
}

bool RecursiveAstVisitor::traverse_ReturnStmt(ReturnStmt* return_stmt) {
    RIFN(visit_ReturnStmt(return_stmt));
    RIFN(dispatch(return_stmt->expr));
    return true;
}

bool RecursiveAstVisitor::traverse_SwitchStmt(SwitchStmt* switch_stmt) {
    RIFN(visit_SwitchStmt(switch_stmt));
    RIFN(dispatch(switch_stmt->value));
    RIFN(dispatch(switch_stmt->body));
    return true;
}

bool RecursiveAstVisitor::traverse_WhileStmt(WhileStmt* while_stmt) {
    RIFN(visit_WhileStmt(while_stmt));
    RIFN(dispatch(while_stmt->condition));
    RIFN(dispatch(while_stmt->body));
    return true;
}

bool RecursiveAstVisitor::traverse_ForStmt(ForStmt* for_stmt) {
    RIFN(visit_ForStmt(for_stmt));
    RIFN(dispatch(for_stmt->init));
    RIFN(dispatch(for_stmt->condition));
    RIFN(dispatch(for_stmt->inc));
    RIFN(dispatch(for_stmt->body));
    return true;
}

//
// Expressions
//

bool RecursiveAstVisitor::traverse_ArraySubscriptExpr(ArraySubscriptExpr* array_subscript_expr) {
    RIFN(visit_ArraySubscriptExpr(array_subscript_expr));
    RIFN(dispatch(array_subscript_expr->lhs));
    RIFN(dispatch(array_subscript_expr->rhs));
    return true;
}

bool RecursiveAstVisitor::traverse_BinaryOpExpr(BinaryOpExpr* binary_op_expr) {
    RIFN(visit_BinaryOpExpr(binary_op_expr));
    RIFN(dispatch(binary_op_expr->lhs));
    RIFN(dispatch(binary_op_expr->rhs));
    return true;
}

bool RecursiveAstVisitor::traverse_CallExpr(CallExpr* call_expr) {
    RIFN(visit_CallExpr(call_expr));
    //RIFN(dispatch(call_expr->template_type));
    for (Expr* arg : call_expr->args) RIFN(dispatch(arg));
    return true;
}

bool RecursiveAstVisitor::traverse_CastExpr(CastExpr* cast_expr) {
    RIFN(visit_CastExpr(cast_expr));
    RIFN(dispatch(cast_expr->expr));
    //RIFN(dispatch(cast_expr->type));
    return true;
}

bool RecursiveAstVisitor::traverse_TernaryExpr(TernaryExpr* ternary_expr) {
    RIFN(visit_TernaryExpr(ternary_expr));
    RIFN(dispatch(ternary_expr->lhs));
    RIFN(dispatch(ternary_expr->rhs));
    return true;
}

bool RecursiveAstVisitor::traverse_MemberExpr(MemberExpr* member_expr) {
    RIFN(visit_MemberExpr(member_expr));
    RIFN(dispatch(member_expr->expr));
    return true;
}

bool RecursiveAstVisitor::traverse_ParenExpr(ParenExpr* paren_expr) {
    RIFN(visit_ParenExpr(paren_expr));
    RIFN(dispatch(paren_expr->expr));
    return true;
}

bool RecursiveAstVisitor::traverse_UnaryOpExpr(UnaryOpExpr* unary_op_expr) {
    RIFN(visit_UnaryOpExpr(unary_op_expr));
    RIFN(dispatch(unary_op_expr->expr));
    return true;
}

//
// Types
//

bool RecursiveAstVisitor::traverse_ArrayType(ArrayType* array_type) {
    RIFN(visit_ArrayType(array_type));
    RIFN(dispatch(array_type->type));
    return true;
}

bool RecursiveAstVisitor::traverse_PointerType(PointerType* pointer_type) {
    RIFN(visit_PointerType(pointer_type));
    RIFN(dispatch(pointer_type->base));
    return true;
}

} // namespace vc
} // namespace t
