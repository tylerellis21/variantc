#ifndef VC_STMT_H_INCLUDE
#define VC_STMT_H_INCLUDE

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
e
};

struct DoStmt : Stmt { };
struct ExprStmt : Stmt { };
struct ForStmt : Stmt { };
struct GotoStmt : Stmt { };
struct IfStmt : Stmt { };
struct LabelStmt : Stmt { };
struct ReturnStmt : Stmt { };
struct SwitchStmt : Stmt { };
struct UseStmt : Stmt { };
struct WhileStmt : Stmt { };

} // namespace vc

#endif // VC_STMT_H_INCLUDE