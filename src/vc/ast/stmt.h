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
    Stmt* stmtParent;
    SourceLocation sourceLocation;

    Stmt(StmtKind stmtKind, Stmt* stmtParent, SourceLocation sourceLocation) :
        stmtKind(stmtKind),
        stmtParent(stmtParent),
        sourceLocation(sourceLocation)
    { }
};

struct BreakStmt : Stmt {
    BreakStmt(Stmt* stmtParent, SourceLocation sourceLocation) :
        Stmt(StmtKind::BreakStmt, stmtParent, sourceLocation)
    { }
};

struct CaseStmt : Stmt { 
    Expr* value;
    Stmt* stmt;

    CaseStmt(Stmt* stmtParent, SourceLocation sourceLocation, Expr* value, Stmt* stmt) :
        Stmt(StmtKind::CaseStmt, stmtParent, sourceLocation),
        value(value),
        stmt(stmt)
    { }
};

struct CompoundStmt : Stmt { 
    SourceRange sourceRange;
    std::vector<Stmt*> statements;

    CompoundStmt(Stmt* stmtParent, SourceRange sourceRange, std::vector<Stmt*> statements) :
        Stmt(StmtKind::CompoundStmt, stmtParent, sourceRange.begin),
        sourceRange(sourceRange),
        statements(statements)
    { }
};

struct ContinueStmt : Stmt { 
    ContinueStmt(Stmt* stmtParent, SourceLocation sourceLocation) :
        Stmt(StmtKind::ContinueStmt, stmtParent, sourceLocation)
    { }
};

struct DeclStmt : Stmt { 
    DeclGroup* declGroup;

    DeclStmt(Stmt* stmtParent, SourceLocation sourceLocation, DeclGroup* declGroup) :
        Stmt(StmtKind::DeclStmt, stmtParent, sourceLocation),
        declGroup(declGroup)
    { }
};

struct DefaultStmt : Stmt { 
    Stmt* stmt;

    DefaultStmt(Stmt* stmtParent, SourceLocation sourceLocation, Stmt* stmt) :
        Stmt(StmtKind::DefaultStmt, stmtParent, sourceLocation)
    { }
};

struct DeferStmt : Stmt { 
    Stmt* stmt;
    
    DeferStmt(Stmt* stmtParent, SourceLocation sourceLocation, Stmt* stmt) :
        Stmt(StmtKind::DeferStmt, stmtParent, sourceLocation),
        stmt(stmt)
    { }
};

struct WhileStmt;

struct DoStmt : Stmt { 
    Stmt* body;
    WhileStmt* whileStmt;

    DoStmt(Stmt* stmtParent, SourceLocation sourceLocation, Stmt* body, WhileStmt* whileStmt) :
        Stmt(StmtKind::WhileStmt, stmtParent, sourceLocation),
        body(body),
        whileStmt(whileStmt)
    { }
};

struct ForStmt : Stmt {
    SourceRange sourceRange;
    Stmt* init;
    Expr* condition;
    Expr* increment;
    Stmt* body;

    ForStmt(
        Stmt* stmtParent, 
        SourceRange sourceRange, 
        Stmt* init, 
        Expr* condition,
        Expr* increment,
        Stmt* body
    ) :
        Stmt(StmtKind::ForStmt, stmtParent, sourceRange.begin),
        sourceRange(sourceRange),
        init(init),
        condition(condition),
        increment(increment),
        body(body)
    { }
};

struct GotoStmt : Stmt { 
    Name* name;

    GotoStmt(Stmt* stmtParent, SourceLocation sourceLocation, Name* name) :
        Stmt(StmtKind::GotoStmt, stmtParent, sourceLocation),
        name(name)
    { }
};

struct IfStmt : Stmt { 
    SourceRange sourceRange;
    Expr* condition;
    Stmt* body;
    Stmt* elseStmt;
    
    IfStmt(
        Stmt* stmtParent, 
        SourceRange sourceRange,
        Expr* condition,
        Stmt* body,
        Stmt* elseStmt
    ) :
        Stmt(StmtKind::IfStmt, stmtParent, sourceRange.begin),
        sourceRange(sourceRange),
        condition(condition),
        body(body),
        elseStmt(elseStmt)
    { }
};

struct LabelStmt : Stmt { 
    Name* name;

    LabelStmt(Stmt* stmtParent, SourceLocation sourceLocation, Name* name) :
        Stmt(StmtKind::LabelStmt, stmtParent, sourceLocation),
        name(name)
    { }
};

struct ReturnStmt : Stmt { 
    Expr* expr;

    ReturnStmt(Stmt* stmtParent, SourceLocation sourceLocation, Expr* expr) :
        Stmt(StmtKind::ReturnStmt, stmtParent, sourceLocation),
        expr(expr)
    { }
};

struct SwitchStmt : Stmt { 
    SourceRange sourceRange;
    Expr* expr;
    Stmt* stmt;

    SwitchStmt(Stmt* stmtParent, SourceRange sourceRange, Expr* expr, Stmt* stmt) :
        Stmt(StmtKind::SwitchStmt, stmtParent, sourceRange.begin),
        expr(expr),
        stmt(stmt)
    { }
};

struct UseStmt : Stmt { 
    Expr* expr;

    UseStmt(Stmt* stmtParent, SourceLocation sourceLocation, Expr* expr) :
        Stmt(StmtKind::UseStmt, stmtParent, sourceLocation),
        expr(expr)
    { }
};

struct WhileStmt : Stmt { 
    SourceRange sourceRange;
    Expr* condition;
    Stmt* body;

    WhileStmt(Stmt* stmtParent, SourceRange sourceRange, Expr* condition, Stmt* body) :
        Stmt(StmtKind::WhileStmt, stmtParent, sourceLocation),
        condition(condition),
        body(body)
    { }
};

} // namespace vc

#endif // VC_STMT_H_INCLUDE