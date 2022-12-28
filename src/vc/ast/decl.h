#ifndef VC_DECL_H_INCLUDE
#define VC_DECL_H_INCLUDE

#include <vc/types.h>
#include <vc/basic/sourcelocation.h>

#include <vector>

namespace vc {

struct DeclGroup;
struct Expr;
struct Stmt;
struct Type;
struct Name;

enum class DeclKind {
    Null = 0,

    // AST Declarations
    EnumConstDecl,
    EnumDecl,
    FunctionArgDecl,
    FunctionDecl,
    ImportDecl,
    InterfaceDecl,
    ModuleDecl,
    NamespaceDecl,
    PackageDecl,
    RecordDecl,
    TypedefDecl,
    UsingDecl,
    VarDecl,

    // Preprocessing declarations
    PPDefDecl,
    PPIfDecl,
    PPUndefDecl,
};

struct Decl {
    DeclKind declKind;
    Decl* parent;
    SourceLocation sourceLocation;

    Decl(DeclKind declKind, Decl* parent, SourceLocation sourceLocation) :
        declKind(declKind),
        parent(parent),
        sourceLocation(sourceLocation)
    { }
};

struct EnumConstDecl : Decl {
    Name* name;
    Expr* value;

    EnumConstDecl(Decl* parent, SourceLocation sourceLocation, Name* name, Expr* value) :
        Decl(DeclKind::EnumConstDecl, parent, sourceLocation),
        name(name),
        value(value)
    {  }
};

struct EnumDecl : Decl {
    SourceRange sourceRange;
    Name* name;
    DeclGroup* declGroup;
    Type* type;

    EnumDecl(
        Decl* parent,
        SourceRange sourceRange,
        Name* name,
        DeclGroup* declGroup,
        Type* type
    ) :
    Decl(DeclKind::EnumDecl, parent, sourceRange.begin),
    sourceRange(sourceRange),
    name(name),
    declGroup(declGroup),
    type(type)
    { }
};

struct VarDecl;
struct FunctionArgDecl : Decl {
    VarDecl* varDecl;

    FunctionArgDecl(Decl* parent, SourceLocation sourceLocation, VarDecl* varDecl) :
        Decl(DeclKind::FunctionArgDecl, parent, sourceLocation),
        varDecl(varDecl)
    { }
};

struct FunctionDecl : Decl {
    Name* name;
    std::vector<FunctionArgDecl*> args;
    Type* returnType;
    Stmt* body;

    FunctionDecl(
        Decl* parent,
        SourceLocation sourceLocation,
        Name* name,
        std::vector<FunctionArgDecl*> args,
        Type* returnType,
        Stmt* body
    ) :
        Decl(DeclKind::FunctionDecl, parent, sourceLocation),
        name(name),
        args(args),
        returnType(returnType),
        body(body)
    { }
};

struct ImportDecl : Decl {
    Name* name;

    ImportDecl(Decl* parent, SourceLocation sourceLocation, Name* name) :
        Decl(DeclKind::ImportDecl, parent, sourceLocation),
        name(name)
    { }
};

struct InterfaceDecl : Decl {
    SourceRange sourceRange;
    Name* name;
    DeclGroup* declGroup;

    InterfaceDecl(
        Decl* parent,
        SourceRange sourceRange,
        Name* name,
        DeclGroup* declGroup
    ) :
        Decl(DeclKind::InterfaceDecl, parent, sourceRange.begin),
        sourceRange(sourceRange),
        name(name),
        declGroup(declGroup)
    { }
};

struct ModuleDecl : Decl {
    DeclGroup* declGroup;

    ModuleDecl(Decl* parent, SourceLocation sourceLocation, DeclGroup* declGroup) :
        Decl(DeclKind::ModuleDecl, parent, sourceLocation),
        declGroup(declGroup)
    { }
};

struct NamespaceDecl : Decl {
    Name* name;
    SourceRange sourceRange;
    DeclGroup* declGroup;

    NamespaceDecl(
        Decl* parent,
        SourceRange sourceRange,
        Name* name,
        DeclGroup* declGroup
    ) :
        Decl(DeclKind::NamespaceDecl, parent, sourceRange.begin),
        name(name),
        sourceRange(sourceRange),
        declGroup(declGroup)
    { }
};

struct PackageDecl : Decl {
    Name* name;

    PackageDecl(Decl* parent, SourceLocation sourceLocation, Name* name) :
        Decl(DeclKind::PackageDecl, parent, sourceLocation)
    { }
};

enum class RecordKind {
    Null = 0,

    AllocatorKind,
    AttributeKind,
    StructKind,
    UnionKind,
};

struct RecordDecl : Decl {
    RecordKind recordKind;
    Name* name;
    DeclGroup* declGroup;

    RecordDecl(
        Decl* parent,
        SourceRange
        sourceRange,
        RecordKind recordKind,
        Name* name,
        DeclGroup* declGroup
    ) :
        Decl(DeclKind::RecordDecl, parent, sourceRange.begin),
        recordKind(recordKind),
        name(name),
        declGroup(declGroup)
    { }
};

struct TypedefDecl : Decl {
    Name* name;
    Type* type;

    TypedefDecl(Decl* parent, SourceLocation sourceLocation, Name* name, Type* type) :
        Decl(DeclKind::TypedefDecl, parent, sourceLocation),
        name(name),
        type(type)
    { }
};

struct UsingDecl : Decl {
    Name* name;

    UsingDecl(Decl* parent, SourceLocation sourceLocation, Name* name) :
        Decl(DeclKind::UsingDecl, parent, sourceLocation),
        name(name)
    { }
};

struct VarDecl : Decl {
    Type* type;
    Name* name;
    Expr* assignment;

    VarDecl(
        Decl* parent,
        SourceLocation sourceLocation,
        Type* type,
        Name* name,
        Expr* assignment
    ) :
        Decl(DeclKind::VarDecl, parent, sourceLocation),
        type(type),
        name(name),
        assignment(assignment)
    { }
};

} // namespace vc

#endif // VC_DECL_H_INCLUDE