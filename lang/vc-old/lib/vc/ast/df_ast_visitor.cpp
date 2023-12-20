#include <vc/ast/df_ast_visitor.h>

// depth first visiting
// we first travel to the deepest node then return going
// up visiting each node as we go.

namespace t {
namespace vc {

//
// Declarations
//
bool DFAstVisitor::traverse_DeclGroup(DeclGroup* dg) {
    for (Decl* decl : dg->decls) RIFN(dispatch(decl));
    return true;
}

bool DFAstVisitor::traverse_ModuleDecl(ModuleDecl* mod) {
    RIFN(visit_ModuleDecl(mod));
    return traverse_DeclGroup(mod->dg);
}

bool DFAstVisitor::traverse_EnumDecl(EnumDecl* enum_decl) { 
    traverse_DeclGroup(enum_decl->dg);
    RIFN(visit_EnumDecl(enum_decl));
    return true;
}

bool DFAstVisitor::traverse_EnumConstDecl(EnumConstDecl* enum_const_decl) {
    dispatch(enum_const_decl->expr);
    RIFN(visit_EnumConstDecl(enum_const_decl));
    return true;
}

bool DFAstVisitor::traverse_FunctionDecl(FunctionDecl* function_decl) {
    for (FunctionArgDecl* arg : function_decl->args) RIFN(dispatch(arg));
    //RIFN(dispatch(function_decl->return_type));
    //RIFN(dispatch(function_decl->template_decl));
    RIFN(dispatch(function_decl->body));
    RIFN(visit_FunctionDecl(function_decl));
    return true; 
}

bool DFAstVisitor::traverse_FunctionArgDecl(FunctionArgDecl* function_arg_decl) {
    RIFN(dispatch(function_arg_decl->var_decl));
    RIFN(visit_FunctionArgDecl(function_arg_decl));
    return true;
}

bool DFAstVisitor::traverse_NamespaceDecl(NamespaceDecl* namespace_decl) {
    RIFN(traverse_DeclGroup(namespace_decl->dg));
    RIFN(visit_NamespaceDecl(namespace_decl));
    return true;
}

bool DFAstVisitor::traverse_RecordDecl(RecordDecl* record_decl) {
    RIFN(traverse_DeclGroup(record_decl->dg));
    RIFN(visit_RecordDecl(record_decl));
    //RIFN(dispatch(record_decl->template_decl));
    //RIFN(dispatch(record_decl->template_type));
    return true;
}

bool DFAstVisitor::traverse_VarDecl(VarDecl* var_decl) {
    //RIFN(dispatch(var_decl->type));
    RIFN(dispatch(var_decl->assignment));
    RIFN(visit_VarDecl(var_decl));
    return true;
}

//
// Statements
//

bool DFAstVisitor::traverse_CaseStmt(CaseStmt* case_stmt) {
    RIFN(dispatch(case_stmt->value));
    RIFN(dispatch(case_stmt->stmt));
    RIFN(visit_CaseStmt(case_stmt));
    return true;
}

bool DFAstVisitor::traverse_CompoundStmt(CompoundStmt* compound_stmt) {
    for (Stmt* sub_stmt : compound_stmt->statements) RIFN(dispatch(sub_stmt));
    RIFN(visit_CompoundStmt(compound_stmt));
    return true;
}

bool DFAstVisitor::traverse_DeclStmt(DeclStmt* decl_stmt) {
    RIFN(traverse_DeclGroup(decl_stmt->dg));
    RIFN(visit_DeclStmt(decl_stmt));
    return true;
}

bool DFAstVisitor::traverse_DefaultStmt(DefaultStmt* default_stmt) {
    RIFN(dispatch(default_stmt->stmt));
    RIFN(visit_DefaultStmt(default_stmt));
    return true;
}

bool DFAstVisitor::traverse_DoStmt(DoStmt* do_stmt) {
    RIFN(dispatch(do_stmt->body));
    RIFN(dispatch(do_stmt->while_stmt));
    RIFN(visit_DoStmt(do_stmt));
    return true;
}

bool DFAstVisitor::traverse_IfStmt(IfStmt* if_stmt) {
    RIFN(dispatch(if_stmt->condition));
    RIFN(dispatch(if_stmt->body));
    RIFN(dispatch(if_stmt->else_stmt));
    RIFN(visit_IfStmt(if_stmt));
    return true;
}

bool DFAstVisitor::traverse_ReturnStmt(ReturnStmt* return_stmt) {
    RIFN(dispatch(return_stmt->expr));
    RIFN(visit_ReturnStmt(return_stmt));
    return true;
}

bool DFAstVisitor::traverse_SwitchStmt(SwitchStmt* switch_stmt) {
    RIFN(dispatch(switch_stmt->value));
    RIFN(dispatch(switch_stmt->body));
    RIFN(visit_SwitchStmt(switch_stmt));
    return true;
}

bool DFAstVisitor::traverse_WhileStmt(WhileStmt* while_stmt) {
    RIFN(dispatch(while_stmt->body));
    RIFN(dispatch(while_stmt->condition));
    RIFN(visit_WhileStmt(while_stmt));
    return true;
}

bool DFAstVisitor::traverse_ForStmt(ForStmt* for_stmt) {
    RIFN(dispatch(for_stmt->init));
    RIFN(dispatch(for_stmt->condition));
    RIFN(dispatch(for_stmt->inc));
    RIFN(dispatch(for_stmt->body));
    return true;
}

//
// Expressions
//

bool DFAstVisitor::traverse_ArraySubscriptExpr(ArraySubscriptExpr* array_subscript_expr) {
    RIFN(dispatch(array_subscript_expr->lhs));
    RIFN(dispatch(array_subscript_expr->rhs));
    RIFN(visit_ArraySubscriptExpr(array_subscript_expr));
    return true;
}

bool DFAstVisitor::traverse_BinaryOpExpr(BinaryOpExpr* binary_op_expr) {
    RIFN(dispatch(binary_op_expr->lhs));
    RIFN(dispatch(binary_op_expr->rhs));
    RIFN(visit_BinaryOpExpr(binary_op_expr));
    return true;
}

bool DFAstVisitor::traverse_CallExpr(CallExpr* call_expr) {
    for (Expr* arg : call_expr->args) RIFN(dispatch(arg));
    RIFN(visit_CallExpr(call_expr));
    return true;
}

bool DFAstVisitor::traverse_CastExpr(CastExpr* cast_expr) {
    RIFN(dispatch(cast_expr->expr));
    RIFN(visit_CastExpr(cast_expr));
    return true;
}

bool DFAstVisitor::traverse_TernaryExpr(TernaryExpr* ternary_expr) {
    RIFN(dispatch(ternary_expr->lhs));
    RIFN(dispatch(ternary_expr->rhs));
    RIFN(visit_TernaryExpr(ternary_expr));
    return true;
}

bool DFAstVisitor::traverse_MemberExpr(MemberExpr* member_expr) {
    RIFN(dispatch(member_expr->expr));
    RIFN(visit_MemberExpr(member_expr));
    return true;
}

bool DFAstVisitor::traverse_ParenExpr(ParenExpr* paren_expr) {
    RIFN(dispatch(paren_expr->expr));
    RIFN(visit_ParenExpr(paren_expr));
    return true;
}

bool DFAstVisitor::traverse_UnaryOpExpr(UnaryOpExpr* unary_op_expr) {
    RIFN(dispatch(unary_op_expr->expr));
    RIFN(visit_UnaryOpExpr(unary_op_expr));
    return true;
}

//
// Types
//

bool DFAstVisitor::traverse_ArrayType(ArrayType* array_type) {
    RIFN(dispatch(array_type->type));
    RIFN(visit_ArrayType(array_type));
    return true;
}

bool DFAstVisitor::traverse_PointerType(PointerType* pointer_type) {
    RIFN(dispatch(pointer_type->base));
    RIFN(visit_PointerType(pointer_type));
    return true;
}

} // namespace vc
} // namespace t