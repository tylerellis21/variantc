#ifndef VC_EXPR_H_INCLUDE
#define VC_EXPR_H_INCLUDE

#include <vc/ast/stmt.h>
#include <vc/ast/type.h>

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

// either a r'' for rune
// or standard ascii char 'a'
struct CharLiteralExpr : Expr {

    union {
        char char_value;
        rune rune_value;
    };

    BuiltinKind builtinKind;

    CharLiteralExpr(Stmt* stmtParent, SourceLocation sourceLocation, char char_value) :
        Expr(ExprKind::CharLiteralExpr, stmtParent, sourceLocation),
        builtinKind(BuiltinKind::Int8),
        char_value(char_value)
    { }

    CharLiteralExpr(Stmt* stmtParent, SourceLocation sourceLocation, rune rune_value) :
        Expr(ExprKind::CharLiteralExpr, stmtParent, sourceLocation),
        builtinKind(BuiltinKind::Rune),
        rune_value(rune_value)
    { }
};

struct IntegerLiteralExpr : Expr {
    union {
        u8 u8_value;
        u16 u16_value;
        u32 u32_value;
        u64 u64_value;
        u64 u128_value[2];
        u64 u256_value[4];
        u64 u512_value[8];
        u64 u1024_value[16];

        i8 i8_value;
        i16 i16_value;
        i32 i32_value;
        i64 i64_value;
        i64 i128_value[2];
        i64 i256_value[4];
        i64 i512_value[8];
        i64 i1024_value[16];
    };

    BuiltinKind builtinKind;

    IntegerLiteralExpr(Stmt* stmtParent, SourceLocation sourceLocation, BuiltinKind builtinKind) :
        Expr(ExprKind::IntegerLiteralExpr, stmtParent, sourceLocation),
        builtinKind(builtinKind)
    { }
};

/*
    R8,
    R16,
    R32,
    R64,
    R128,
    R256,
    R512,
    R1024,
    Decimal
*/

// real32,
// real64
struct RealLiteralExpr : Expr {
    BuiltinKind builtinKind;
};

// how to handle ascii/utf8, utf16 and utf32 strings? utf32("test")
/*
    CStr,
    Utf8,
    Utf16,
    Utf32,
*/
struct StringLiteralExpr : Expr {
    BuiltinKind builtinKind;
};

} // namespace vc

#endif // VC_EXPR_H_INCLUDE
