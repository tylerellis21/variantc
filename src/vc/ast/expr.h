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

    Expr(ExprKind exprKind, Stmt* parentStmt, SourceLocation sourceLocation) :
        Stmt(StmtKind::ExprStmt, parentStmt, sourceLocation),
        exprKind(exprKind)
    { }
};

struct ArraySubscriptExpr : Expr {
    SourceRange sourceRange;
    Expr* lhs;
    Expr* rhs;

    ArraySubscriptExpr(Stmt* parentStmt, SourceLocation sourceLocation, Expr* lhs, Expr* rhs) :
        Expr(ExprKind::ArraySubscriptExpr, parentStmt, sourceLocation)
    { }
};

struct BinaryOpExpr : Expr {
    SourceRange sourceRange;
    Expr* lhs;
    Expr* rhs;
    TokenKind op;

    BinaryOpExpr(Stmt* parentStmt, SourceRange sourceRange, Expr* lhs, Expr* rhs, TokenKind op) :
        Expr(ExprKind::BinaryOpExpr, parentStmt, sourceRange.begin),
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

    CallExpr(Stmt* parentStmt, SourceRange sourceRange, Name* name, std::vector<Expr*> args) :
        Expr(ExprKind::CallExpr, parentStmt, sourceRange.begin),
        sourceRange(sourceRange),
        name(name),
        args(args)
    { }
};

struct CastExpr : Expr {
    SourceRange sourceRange;
    Expr* expr;
    Type* type;

    CastExpr(Stmt* parentStmt, SourceRange sourceRange, Expr* expr, Type* type) :
        Expr(ExprKind::CastExpr, parentStmt, sourceRange.begin),
        sourceRange(sourceRange),
        expr(expr),
        type(type)
    { }
};

struct DeclRefExpr : Expr {
    Name* name;

    DeclRefExpr(Stmt* parentStmt, SourceLocation sourceLocation, Name* name) :
        Expr(ExprKind::DeclRefExpr, parentStmt, sourceLocation),
        name(name)
    { }
};

struct InitalizerExpr : Expr {
    SourceRange sourceRange;
    std::vector<Expr*> values;

    InitalizerExpr(Stmt* parentStmt, SourceRange sourceRange, std::vector<Expr*> values) :
        Expr(ExprKind::InitalizerExpr, parentStmt, sourceRange.begin),
        sourceRange(sourceRange),
        values(values)
    { }
};

struct MemberExpr : Expr {
    SourceRange sourceRange;
    Name* name;
    Expr* expr;

    MemberExpr(Stmt* parentStmt, SourceRange sourceRange, Name* name, Expr* expr) :
        Expr(ExprKind::MemberExpr, parentStmt, sourceRange.begin),
        sourceRange(sourceRange),
        name(name),
        expr(expr)
    { }
};

struct ParenExpr : Expr {
    SourceRange sourceRange;
    Expr* expr;

    ParenExpr(Stmt* parentStmt, SourceRange sourceRange, Expr* expr) :
        Expr(ExprKind::ParenExpr, parentStmt, sourceRange.begin),
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
        Stmt* parentStmt,
        SourceRange sourceRange,
        Expr* condition,
        Expr* lhs,
        Expr* rhs
    ) :
        Expr(ExprKind::TernaryExpr, parentStmt, sourceRange.begin),
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
        Stmt* parentStmt,
        SourceRange sourceRange,
        bool isPostfix,
        Expr* expr,
        TokenKind op
    ) :
        Expr(ExprKind::UnaryOpExpr, parentStmt, sourceRange.begin),
        sourceRange(sourceRange),
        isPostfix(isPostfix),
        expr(expr),
        op(op)
    { }
};

struct BooleanLiteralExpr : Expr {
    bool value;

    BooleanLiteralExpr(Stmt* parentStmt, SourceLocation sourceLocation, bool value) :
        Expr(ExprKind::BooleanLiteralExpr, parentStmt, sourceLocation),
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

    CharLiteralExpr(Stmt* parentStmt, SourceLocation sourceLocation, char char_value) :
        Expr(ExprKind::CharLiteralExpr, parentStmt, sourceLocation),
        builtinKind(BuiltinKind::Int8),
        char_value(char_value)
    { }

    CharLiteralExpr(Stmt* parentStmt, SourceLocation sourceLocation, rune rune_value) :
        Expr(ExprKind::CharLiteralExpr, parentStmt, sourceLocation),
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

    IntegerLiteralExpr(Stmt* parentStmt, SourceLocation sourceLocation, BuiltinKind builtinKind) :
        Expr(ExprKind::IntegerLiteralExpr, parentStmt, sourceLocation),
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
