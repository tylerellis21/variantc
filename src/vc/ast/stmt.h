#ifndef VC_STMT_H_INCLUDE
#define VC_STMT_H_INCLUDE

#include <vc/basic/sourcelocation.h>

#include <vector>

namespace vc {

enum class StmtKind {
    Null = 0,

    BreakStmt,
    CaseStmt,
    CompoundStmt,
    ContinueStmt,
    DeclStmt,
    DefaultStmt,
    DeferStmt,
    DoStmt,
    ExprStmt,
    ForStmt,
    GotoStmt,
    IfStmt,
    LabelStmt,
    ReturnStmt,
    SwitchStmt,
    UseStmt,
    WhileStmt,
};

struct DeclGroup;
struct Type;
struct Name;
struct Expr;

struct Stmt {
    StmtKind stmtKind;
    Stmt* parentStmt;
    SourceLocation sourceLocation;

    Stmt(StmtKind stmtKind, Stmt* parentStmt, SourceLocation sourceLocation) :
        stmtKind(stmtKind),
        parentStmt(parentStmt),
        sourceLocation(sourceLocation)
    { }
};

inline void setStmtParent(Stmt* stmt, Stmt* parent) {
    if (stmt) {
        stmt->parentStmt = parent;
    }
}

struct BreakStmt : Stmt {
    BreakStmt(Stmt* parentStmt, SourceLocation sourceLocation) :
        Stmt(StmtKind::BreakStmt, parentStmt, sourceLocation)
    { }
};

struct CaseStmt : Stmt {
    Expr* valueExpr;
    Stmt* bodyStmt;

    CaseStmt(Stmt* parentStmt, SourceLocation sourceLocation, Expr* valueExpr, Stmt* bodyStmt) :
        Stmt(StmtKind::CaseStmt, parentStmt, sourceLocation),
        valueExpr(valueExpr),
        bodyStmt(bodyStmt)
    { }
};

struct CompoundStmt : Stmt {
    SourceRange sourceRange;
    std::vector<Stmt*> statements;

    CompoundStmt(Stmt* parentStmt, SourceRange sourceRange, std::vector<Stmt*> statements) :
        Stmt(StmtKind::CompoundStmt, parentStmt, sourceRange.begin),
        sourceRange(sourceRange),
        statements(statements)
    { }
};

struct ContinueStmt : Stmt {
    ContinueStmt(Stmt* parentStmt, SourceLocation sourceLocation) :
        Stmt(StmtKind::ContinueStmt, parentStmt, sourceLocation)
    { }
};

struct DeclStmt : Stmt {
    DeclGroup* declGroup;

    DeclStmt(Stmt* parentStmt, SourceLocation sourceLocation, DeclGroup* declGroup) :
        Stmt(StmtKind::DeclStmt, parentStmt, sourceLocation),
        declGroup(declGroup)
    { }
};

struct DefaultStmt : Stmt {
    Stmt* bodyStmt;

    DefaultStmt(Stmt* parentStmt, SourceLocation sourceLocation, Stmt* bodyStmt) :
        Stmt(StmtKind::DefaultStmt, parentStmt, sourceLocation)
    { }
};

struct DeferStmt : Stmt {
    Stmt* bodyStmt;

    DeferStmt(Stmt* parentStmt, SourceLocation sourceLocation, Stmt* bodyStmt) :
        Stmt(StmtKind::DeferStmt, parentStmt, sourceLocation),
        bodyStmt(bodyStmt)
    { }
};

struct WhileStmt;

struct DoStmt : Stmt {
    Stmt* bodyStmt;
    Expr* whileExpr;

    DoStmt(
        Stmt* parentStmt,
        SourceLocation sourceLocation,
        Stmt* bodyStmt,
        Expr* whileExpr
    ) :
        Stmt(StmtKind::WhileStmt, parentStmt, sourceLocation),
        bodyStmt(bodyStmt),
        whileExpr(whileExpr)
    { }
};

struct ForStmt : Stmt {
    SourceRange sourceRange;
    Stmt* initExpr;
    Expr* conditionExpr;
    Expr* incrementExpr;
    Stmt* bodyStmt;

    ForStmt(
        Stmt* parentStmt,
        SourceLocation sourceLocation,
        SourceRange sourceRange,
        Expr* initExpr,
        Expr* conditionExpr,
        Expr* incrementExpr,
        Stmt* bodyStmt
    ) :
        Stmt(StmtKind::ForStmt, parentStmt, sourceLocation),
        sourceRange(sourceRange),
        initExpr(initExpr),
        conditionExpr(conditionExpr),
        incrementExpr(incrementExpr),
        bodyStmt(bodyStmt)
    { }
};

struct GotoStmt : Stmt {
    Name name;

    GotoStmt(Stmt* parentStmt, SourceLocation sourceLocation, Name name) :
        Stmt(StmtKind::GotoStmt, parentStmt, sourceLocation),
        name(name)
    { }
};

struct IfStmt : Stmt {
    SourceRange sourceRange;
    Expr* conditionExpr;
    Stmt* bodyStmt;
    Stmt* elseStmt;

    IfStmt(
        Stmt* parentStmt,
        SourceLocation sourceLocation,
        SourceRange sourceRange,
        Expr* conditionExpr,
        Stmt* bodyStmt,
        Stmt* elseStmt
    ) :
        Stmt(StmtKind::IfStmt, parentStmt, sourceLocation),
        sourceRange(sourceRange),
        conditionExpr(conditionExpr),
        bodyStmt(bodyStmt),
        elseStmt(elseStmt)
    { }
};

struct LabelStmt : Stmt {
    Name name;

    LabelStmt(Stmt* parentStmt, SourceLocation sourceLocation, Name name) :
        Stmt(StmtKind::LabelStmt, parentStmt, sourceLocation),
        name(name)
    { }
};

struct ReturnStmt : Stmt {
    Expr* expr;

    ReturnStmt(Stmt* parentStmt, SourceLocation sourceLocation, Expr* expr) :
        Stmt(StmtKind::ReturnStmt, parentStmt, sourceLocation),
        expr(expr)
    { }
};

struct SwitchStmt : Stmt {
    SourceRange sourceRange;
    Expr* conditionExpr;
    Stmt* bodyStmt;

    SwitchStmt(
        Stmt* parentStmt,
        SourceLocation sourceLocation,
        SourceRange sourceRange,
        Expr* conditionExpr,
        Stmt* bodyStmt
    ) :
        Stmt(StmtKind::SwitchStmt, parentStmt, sourceRange.begin),
        conditionExpr(conditionExpr),
        bodyStmt(bodyStmt)
    { }
};

struct UseStmt : Stmt {
    Expr* expr;

    UseStmt(Stmt* parentStmt, SourceLocation sourceLocation, Expr* expr) :
        Stmt(StmtKind::UseStmt, parentStmt, sourceLocation),
        expr(expr)
    { }
};

struct WhileStmt : Stmt {
    SourceRange sourceRange;
    Expr* conditionExpr;
    Stmt* bodyStmt;

    WhileStmt(
        Stmt* parentStmt,
        SourceLocation sourceLocation,
        SourceRange sourceRange,
        Expr* conditionExpr,
        Stmt* bodyStmt
    ) :
        Stmt(StmtKind::WhileStmt, parentStmt, sourceLocation),
        conditionExpr(conditionExpr),
        bodyStmt(bodyStmt)
    { }
};

} // namespace vc

#endif // VC_STMT_H_INCLUDE