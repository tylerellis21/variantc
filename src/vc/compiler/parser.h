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

    bool parseStmt(Stmt* stmtParent, Stmt** out);

    bool parseCompoundStmt(Stmt* stmtParent, Stmt** out);
    bool parseOptionalCompoundStmt(Stmt* stmtParent, Stmt** out);
    bool parseBreakStmt(Stmt* stmtParent, Stmt** out);
    bool parseContinueStmt(Stmt* stmtParent, Stmt** out);
    bool parseTemplateStmt(Stmt* stmtParent, Stmt** out);
    bool parseDeclStmt(Stmt* stmtParent, Stmt** out);
    bool parseDoStmt(Stmt* stmtParent, Stmt** out);
    bool parseForStmt(Stmt* stmtParent, Stmt** out);
    bool parseIfStmt(Stmt* stmtParent, Stmt** out);
    bool parseLabelStmt(Stmt* stmtParent, Stmt** out);
    bool parseGotoStmt(Stmt* stmtParent, Stmt** out);
    bool parseSwitchStmt(Stmt* stmtParent, Stmt** out);
    bool parseWhileStmt(Stmt* stmtParent, Stmt** out);
    bool parseDefaultStmt(Stmt* stmtParent, Stmt** out);
    bool parseCaseStmt(Stmt* stmtParent, Stmt** out);
    bool parseReturnStmt(Stmt* stmtParent, Stmt** out);

    ///
    /// Expression parsing methods
    ///

    Expr* exprError();

    Expr* parseExpr(Stmt* stmtParent);

    Expr* parseAssignmentExpr(Stmt* stmtParent);
    Expr* parseArraySubscriptExpr(Stmt* stmtParent, Expr* lhs);
    Expr* parseUnaryExpr(Stmt* stmtParent, Expr* lhs, bool postfix);
    Expr* parseRhsBinaryOp(Stmt* stmtParent, Expr* lhs, i32 minPrecedence);
    Expr* parseCallExpr(Stmt* stmtParent, bool expectSemi, Name* name = 0, Type* templateType = 0);
    Expr* parseCastExpr(Stmt* stmtParent);
    Expr* parseTernaryExpr(Stmt* stmtParent, Expr* condition);
    Expr* parsePostfixExpr(Stmt* stmtParent, Expr* lhs, bool postfix);
    Expr* parseDeclRefExpr(Stmt* stmtParent);
    Expr* parseInitalizerExpr(Stmt* stmtParent);
    Expr* parseLiteralExpr(Stmt* stmtParent);
    Expr* parseParenExpr(Stmt* stmtParent);
    Expr* parseMemberExpr(Stmt* stmtParent);

    ///
    /// Type parsing methods
    ///

    bool parseType(Type** type, bool firstCall = true);

    bool parseBasicType(Type** type);
    bool parsePointerType(Type** type);
    bool parseDeclRefType(Type** type, Name* name = 0);
    bool parseArrayType(Type** type);
    bool parseVarargType(Type** type);

    bool parseTemplateType(Type** type, Name* name = 0);
};

} // namespace vc

#endif // VC_PARSER_H_INCLUDE