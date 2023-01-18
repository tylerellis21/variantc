#ifndef VC_PARSER_H_INCLUDE
#define VC_PARSER_H_INCLUDE

#include <vc/basic/token.h>
#include <vc/ast/name.h>
#include <vc/ast/decl.h>
#include <vc/ast/declgroup.h>

namespace vc {

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

    SourceLocation loc();
    SourceLocation consume();

    bool expect(TokenKind tokenKind);
    bool expectConsume(TokenKind tokenKind);
    bool expectSemi();

    bool parseName(Name* name, bool fullyQualifiedName);

    bool parseDeclaration(Decl* parentDecl, DeclGroup* declGroup);

    bool parsePackageDecl(Decl* parent, DeclGroup* dg);
    bool parseUsingDecl(Decl* parent, DeclGroup* dg);
    bool parseTypedefDecl(Decl* parent, DeclGroup* dg);
    bool parseTemplateDecl(Decl* parent, Decl** out);
    bool parseImportDecl(Decl* parent, DeclGroup* dg);
    bool parseEnumDecl(Decl* parent, DeclGroup* dg);
    bool parseNamespaceDecl(Decl* parent, DeclGroup* dg);
    bool parseRecordDecl(Decl* parent, DeclGroup* dg);
    bool parseFunctionDecl(Decl* parent, DeclGroup* dg);
    bool parseFunctionArgDecl(Decl* parent, FunctionArgDecl** out);
    bool parseSingleVarDecl(Decl* parent, VarDecl** out, Type* type = 0);
    bool parseCompoundVarDecl(Decl* parent, DeclGroup* dg, Type* type = 0);

    Stmt* parseStatement(Stmt* parentStmt, DeclGroup* declGroup);

    Expr* parseExpression(Expr* parentExpr, DeclGroup* declGroup);

    Type* parseType(Type* parentType, DeclGroup* declGroup);
};

} // namespace vc

#endif // VC_PARSER_H_INCLUDE