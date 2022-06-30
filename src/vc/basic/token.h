#ifndef VC_TOKEN_H_INCLUDE
#define VC_TOKEN_H_INCLUDE

#include <string>

#include <vc/basic/sourcelocation.h>

namespace vc {

enum TokenKind {
    Null = 0,

    BooleanLiteral,
    CharacterLiteral,
    IntegerLiteral,
    RealLiteral,
    StringLiteral,

    Identifier,

    Align,
    Allocator,
    As,
    Async,
    Atomic,
    Attribute,
    Await,
    Base,
    Catch,
    Class,
    Const,
    Continue,
    Def,
    Defer,
    Delegate,
    Delete,
    Do,
    Else,
    Enum,
    Explicit,
    Export,
    Extern,
    False,
    For,
    Foreach,
    Goto,
    If,
    Implicit,
    Import,
    Interface,
    Lock,
    Nameof,
    Namespace,
    New,
    Operator,
    Package,
    Params,
    Return,
    Sizeof,
    Static,
    Struct,
    Switch,
    This,
    Throw,
    True,
    Try,
    Typeof,
    Union,
    Use,
    Using,
    Var,
    Void,
    Volatile,
    While,
    Yield,
};

struct Token {
    TokenKind kind;
    SourceLocation loc;
    std::string string;
};

}

#endif // VC_TOKEN_H_INCLUDE
