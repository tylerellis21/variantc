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

struct BreakStmt : Stmt {
    BreakStmt(Stmt* parentStmt, SourceLocation sourceLocation) :
        Stmt(StmtKind::BreakStmt, parentStmt, sourceLocation)
    { }
};

struct CaseStmt : Stmt {
    Expr* value;
    Stmt* stmt;

    CaseStmt(Stmt* parentStmt, SourceLocation sourceLocation, Expr* value, Stmt* stmt) :
        Stmt(StmtKind::CaseStmt, parentStmt, sourceLocation),
        value(value),
        stmt(stmt)
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
    Stmt* stmt;

    DefaultStmt(Stmt* parentStmt, SourceLocation sourceLocation, Stmt* stmt) :
        Stmt(StmtKind::DefaultStmt, parentStmt, sourceLocation)
    { }
};

struct DeferStmt : Stmt {
    Stmt* stmt;

    DeferStmt(Stmt* parentStmt, SourceLocation sourceLocation, Stmt* stmt) :
        Stmt(StmtKind::DeferStmt, parentStmt, sourceLocation),
        stmt(stmt)
    { }
};

struct WhileStmt;

struct DoStmt : Stmt {
    Stmt* body;
    WhileStmt* whileStmt;

    DoStmt(Stmt* parentStmt, SourceLocation sourceLocation, Stmt* body, WhileStmt* whileStmt) :
        Stmt(StmtKind::WhileStmt, parentStmt, sourceLocation),
        body(body),
        whileStmt(whileStmt)
    { }
};

struct ForStmt : Stmt {
    SourceRange sourceRange;
    Stmt* initStmt;
    Expr* conditionStmt;
    Expr* incrementStmt;
    Stmt* bodyStmt;

    ForStmt(
        Stmt* parentStmt,
        SourceLocation sourceLocation,
        SourceRange sourceRange,
        Stmt* initStmt,
        Expr* conditionStmt,
        Expr* incrementStmt,
        Stmt* bodyStmt
    ) :
        Stmt(StmtKind::ForStmt, parentStmt, sourceLocation),
        sourceRange(sourceRange),
        initStmt(initStmt),
        conditionStmt(conditionStmt),
        incrementStmt(incrementStmt),
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
    Expr* conditionStmt;
    Stmt* bodyStmt;
    Stmt* elseStmt;

    IfStmt(
        Stmt* parentStmt,
        SourceLocation sourceLocation,
        SourceRange sourceRange,
        Expr* conditionStmt,
        Stmt* bodyStmt,
        Stmt* elseStmt
    ) :
        Stmt(StmtKind::IfStmt, parentStmt, sourceLocation),
        sourceRange(sourceRange),
        conditionStmt(conditionStmt),
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
    Expr* expr;
    Stmt* stmt;

    SwitchStmt(Stmt* parentStmt, SourceRange sourceRange, Expr* expr, Stmt* stmt) :
        Stmt(StmtKind::SwitchStmt, parentStmt, sourceRange.begin),
        expr(expr),
        stmt(stmt)
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
    Expr* condition;
    Stmt* body;

    WhileStmt(Stmt* parentStmt, SourceRange sourceRange, Expr* condition, Stmt* body) :
        Stmt(StmtKind::WhileStmt, parentStmt, sourceLocation),
        condition(condition),
        body(body)
    { }
};

} // namespace vc

#endif // VC_STMT_H_INCLUDE