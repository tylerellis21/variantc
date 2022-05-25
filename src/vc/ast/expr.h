#ifndef VC_EXPR_H_INCLUDE
#define VC_EXPR_H_INCLUDE

#include <vc/ast/stmt.h>
#include <vc/basic/token.h>

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
    ExprKind exprKind;

    Expr(ExprKind exprKind, Stmt* stmtParent, SourceLocation sourceLocation) :
        Stmt(StmtKind::ExprStmt, stmtParent, sourceLocation),
        exprKind(exprKind)
    { }
};

struct ArraySubscriptExpr : Expr {
    SourceRange sourceRange;
    Expr* lhs;
    Expr* rhs;

    ArraySubscriptExpr(Stmt* stmtParent, SourceLocation sourceLocation, Expr* lhs, Expr* rhs) :
        Expr(ExprKind::ArraySubscriptExpr, stmtParent, sourceLocation)
    { }
};

struct BinaryOpExpr : Expr { 
    SourceRange sourceRange;
    Expr* lhs;
    Expr* rhs;
    TokenKind op;

    BinaryOpExpr(Stmt* stmtParent, SourceRange sourceRange, Expr* lhs, Expr* rhs, TokenKind op) :
        Expr(ExprKind::BinaryOpExpr, stmtParent, sourceRange.begin),
        sourceRange(sourceRange),
        lhs(lhs),
        rhs(rhs),
        op(op)
    { }
};

struct CallExpr : Expr { 
    SourceRange sourceRange;
    Name* name;
    std::vector<Expr*> args;

    CallExpr(Stmt* stmtParent, SourceRange sourceRange, Name* name, std::vector<Expr*> args) :
        Expr(ExprKind::CallExpr, stmtParent, sourceRange.begin),
        sourceRange(sourceRange),
        name(name),
        args(args)
    { }
};

struct CastExpr : Expr { 
    SourceRange sourceRange;
    Expr* expr;
    Type* type;

    CastExpr(Stmt* stmtParent, SourceRange sourceRange, Expr* expr, Type* type) :
        Expr(ExprKind::CastExpr, stmtParent, sourceRange.begin),
        sourceRange(sourceRange),
        expr(expr),
        type(type)
    { }
};

struct DeclRefExpr : Expr { 
    Name* name;

    DeclRefExpr(Stmt* stmtParent, SourceLocation sourceLocation, Name* name) :
        Expr(ExprKind::DeclRefExpr, stmtParent, sourceLocation),
        name(name)
    { }
};

struct InitalizerExpr : Expr { 
    SourceRange sourceRange;
    std::vector<Expr*> values;

    InitalizerExpr(Stmt* stmtParent, SourceRange sourceRange, std::vector<Expr*> values) :
        Expr(ExprKind::InitalizerExpr, stmtParent, sourceRange.begin),
        sourceRange(sourceRange),
        values(values)
    { }
};

struct MemberExpr : Expr { 
    SourceRange sourceRange;
    Name* name;
    Expr* expr;

    MemberExpr(Stmt* stmtParent, SourceRange sourceRange, Name* name, Expr* expr) :
        Expr(ExprKind::MemberExpr, stmtParent, sourceRange.begin),
        sourceRange(sourceRange),
        name(name),
        expr(expr)
    { }
};

struct ParenExpr : Expr {
    SourceRange sourceRange;
    Expr* expr;

    ParenExpr(Stmt* stmtParent, SourceRange sourceRange, Expr* expr) :
        Expr(ExprKind::ParenExpr, stmtParent, sourceRange.begin),
        sourceRange(sourceRange),
        expr(expr)
    { }
};

struct TernaryExpr : Expr { 
    SourceRange sourceRange;
    Expr* condition;
    Expr* lhs;
    Expr* rhs;

    TernaryExpr(
        Stmt* stmtParent, 
        SourceRange sourceRange,
        Expr* condition,
        Expr* lhs,
        Expr* rhs
    ) :
        Expr(ExprKind::TernaryExpr, stmtParent, sourceRange.begin),
        sourceRange(sourceRange),
        condition(condition),
        lhs(lhs),
        rhs(rhs)
    { }
};

struct UnaryOpExpr : Expr { 
    SourceRange sourceRange;
    bool isPostfix;
    Expr* expr;
    TokenKind op;

    UnaryOpExpr(
        Stmt* stmtParent,
        SourceRange sourceRange,
        bool isPostfix,
        Expr* expr,
        TokenKind op
    ) :
        Expr(ExprKind::UnaryOpExpr, stmtParent, sourceRange.begin),
        sourceRange(sourceRange),
        isPostfix(isPostfix),
        expr(expr),
        op(op)
    { }
};

struct BooleanLiteralExpr : Expr { 
    bool value;

    BooleanLiteralExpr(Stmt* stmtParent, SourceLocation sourceLocation, bool value) :
        Expr(ExprKind::BooleanLiteralExpr, stmtParent, sourceLocation),
        value(value)
    { }
};

struct CharLiteralExpr : Expr { 

};

// u8
// u16
// u32
//....
//
// i8
// i16
// i32
// i64
// .....
struct IntegerLiteralExpr : Expr { 

};

// real32, 
// real64
struct RealLiteralExpr : Expr { 

};

// how to handle ascii/utf8, utf16 and utf32 strings?
struct StringLiteralExpr : Expr { 

};

} // namespace vc

#endif // VC_EXPR_H_INCLUDE