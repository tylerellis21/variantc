#include <vc/val.h>
#include <vc/compiler.h>
#include <vc/basic/report.h>

namespace t {
namespace vc {

bool Val::visit_Expr(Expr* expr) {
    return true;
}

bool Val::visit_ArraySubscriptExpr(ArraySubscriptExpr* array_subscript_expr) {
    return true;
}

bool Val::visit_BinaryOpExpr(BinaryOpExpr* binary_op_expr) {
    return true;
}

bool Val::visit_CallExpr(CallExpr* call_expr) {
    return true;
}

bool Val::visit_CastExpr(CastExpr* cast_expr) {
    return true;
}

bool Val::visit_TernaryExpr(TernaryExpr* ternary_expr) {
    return true;
}

bool Val::visit_DeclRefExpr(DeclRefExpr* decl_ref_expr) {

    Name* ref_name = decl_ref_expr->name;
    Decl* ref = search_decl_scope(ref_name, decl_ref_expr->scope);

    Decl* scope = find_decl_scope(decl_stack.top());
    
    decl_ref_expr->scope = scope;
    decl_ref_expr->ref = ref;

    return true;
}

bool Val::visit_MemberExpr(MemberExpr* member_expr) {
    return true;
}

bool Val::visit_ParenExpr(ParenExpr* paren_expr) {
    return true;
}

bool Val::visit_UnaryOpExpr(UnaryOpExpr* unary_op_expr) {
    return true;
}

bool Val::visit_InitalizerExpr(InitalizerExpr* initalizer_expr) {
    return true;
}

bool Val::visit_BooleanLiteral(BooleanLiteral* boolean_literal) {
    return true;
}

bool Val::visit_CharLiteral(CharLiteral* char_literal) {
    return true;
}

bool Val::visit_IntegerLiteral(IntegerLiteral* integer_literal) {
    return true;
}

bool Val::visit_RealLiteral(RealLiteral* real_literal) {
    return true;
}

bool Val::visit_StringLiteral(StringLiteral* string_literal) {
    return true;
}

} // namespace vc
} // namespace t

