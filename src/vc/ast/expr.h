#ifndef VC_EXPR_H_INCLUDE
#define VC_EXPR_H_INCLUDE
#include <vc/ast/stmt.h>

namespace vc {

enum class ExprKind {
    Null = 0,
    ArraySubscriptExpr,
    BinaryOpExpr,
    CallExpr,
    CastExpr,
    DeclRefExpr,
    InitalizerExpr,
    MemberExpr,
    ParenExpr,
    TernaryExpr,
    UnaryOpExpr,

    BooleanLiteralExpr,
    CharLiteralExpr,
    IntegerLiteralExpr,
    RealLiteralExpr,
    StringLiteralExpr,
};

struct Expr : Stmt {
    
};

} // namespace vc

#endif // VC_EXPR_H_INCLUDE