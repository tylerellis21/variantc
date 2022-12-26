#ifndef VC_PARSER_H_INCLUDE
#define VC_PARSER_H_INCLUDE

#include <vc/basic/token.h>

namespace vc {

struct Decl;
struct DeclGroup;
struct Stmt;
struct Expr;
struct Type;

struct Lexer;

struct Parser {
    Token prev;
    Token current;
    Token next;

    Lexer* lexer;

    Parser(Lexer* lexer);

    bool valid();
    bool open();

    SourceLocation consume();

    bool expect(TokenKind tokenKind);
    bool expectConsume(TokenKind tokenKind);
    bool expectSemi();

    Decl* parseDeclaration(Decl* parentDecl, DeclGroup* declGroup);

    Stmt* parseStatement(Stmt* parentStmt, DeclGroup* declGroup);

    Expr* parseExpression(Expr* parentExpr, DeclGroup* declGroup);

    Type* parseType(Type* parentType, DeclGroup* declGroup);
};

} // namespace vc

#endif // VC_PARSER_H_INCLUDE