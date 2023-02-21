#ifndef VC_PARSER_H_INCLUDE
#define VC_PARSER_H_INCLUDE

#include <vc/basic/token.h>
#include <vc/ast/name.h>
#include <vc/ast/decl.h>
#include <vc/ast/declgroup.h>
#include <vc/ast/stmt.h>
#include <vc/ast/expr.h>
#include <vc/ast/type.h>

namespace vc {

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

    bool parseDecl(Decl* parentDecl, DeclGroup* declGroup);

    bool parseUsingDecl(Decl* parent, DeclGroup* declGroup);
    bool parseTypedefDecl(Decl* parent, DeclGroup* declGroup);
    bool parseImportDecl(Decl* parent, DeclGroup* declGroup);
    bool parseEnumDecl(Decl* parent, DeclGroup* declGroup);
    bool parseNamespaceDecl(Decl* parent, DeclGroup* declGroup);
    bool parseRecordDecl(Decl* parent, DeclGroup* declGroup);
    bool parseFunctionDecl(Decl* parent, DeclGroup* declGroup);
    bool parseFunctionArgDecl(Decl* parent, FunctionArgDecl** out);
    bool parseSingleVarDecl(Decl* parent, VarDecl** out, Type* type = 0);
    bool parseCompoundVarDecl(Decl* parent, DeclGroup* declGroup, Type* type = 0);

    // bool parseTemplateDecl(Decl* parent, DeclGroup* declGroup, TemplateDecl** templateDecl);
    // bool parseTemplateDecl(Decl* parent, DeclGroup* declGroup);

    bool parseStmt(Stmt* parentStmt, Stmt** out);

    bool parseCompoundStmt(Stmt* parentStmt, Stmt** out);
    bool parseOptionalCompoundStmt(Stmt* parentStmt, Stmt** out);
    bool parseBreakStmt(Stmt* parentStmt, Stmt** out);
    bool parseContinueStmt(Stmt* parentStmt, Stmt** out);
    bool parseDeclStmt(Stmt* parentStmt, Stmt** out);
    bool parseDoStmt(Stmt* parentStmt, Stmt** out);
    bool parseForStmt(Stmt* parentStmt, Stmt** out);
    bool parseIfStmt(Stmt* parentStmt, Stmt** out);
    bool parseLabelStmt(Stmt* parentStmt, Stmt** out);
    bool parseGotoStmt(Stmt* parentStmt, Stmt** out);
    bool parseSwitchStmt(Stmt* parentStmt, Stmt** out);
    bool parseWhileStmt(Stmt* parentStmt, Stmt** out);
    bool parseDefaultStmt(Stmt* parentStmt, Stmt** out);
    bool parseCaseStmt(Stmt* parentStmt, Stmt** out);
    bool parseReturnStmt(Stmt* parentStmt, Stmt** out);

    // bool parseTemplateStmt(Stmt* parentStmt, TemplateDecl** out);

    ///
    /// Expression parsing methods
    ///

    Expr* exprError();

    Expr* parseExpr(Stmt* parentStmt);

    Expr* parseAssignmentExpr(Stmt* parentStmt);
    Expr* parseArraySubscriptExpr(Stmt* parentStmt, Expr* lhs);
    Expr* parseUnaryExpr(Stmt* parentStmt, Expr* lhs, bool postfix);
    Expr* parseRhsBinaryOp(Stmt* parentStmt, Expr* lhs, i32 minPrecedence);
    // Expr* parseCallExpr(Stmt* parentStmt, bool expectSemi, Name name, Type* templateType = 0);
    Expr* parseCallExpr(Stmt* parentStmt, bool expectSemi);
    Expr* parseCastExpr(Stmt* parentStmt);
    Expr* parseTernaryExpr(Stmt* parentStmt, Expr* condition);
    Expr* parsePostfixExpr(Stmt* parentStmt, Expr* lhs, bool postfix);
    Expr* parseDeclRefExpr(Stmt* parentStmt);
    Expr* parseInitalizerExpr(Stmt* parentStmt);
    Expr* parseParenExpr(Stmt* parentStmt);
    Expr* parseMemberExpr(Stmt* parentStmt);

    Expr* parseLiteralExpr(Stmt* parentStmt);
    Expr* parseBooleanLiteralExpr(Stmt* parentStmt);
    Expr* parseCharacterLiteralExpr(Stmt* parentStmt);
    Expr* parseStringLiteralExpr(Stmt* parentStmt);
    Expr* parseIntegerLiteralExpr(Stmt* parentStmt);
    Expr* parseRealLiteralExpr(Stmt* parentStmt);

    ///
    /// Type parsing methods
    ///

    bool parseType(Type** type, bool firstCall = true);

    bool parseBuiltinType(Type** type);
    bool parsePointerType(Type** type);
    bool parseDeclRefType(Type** type);
    bool parseArrayType(Type** type);
    bool parseVarargType(Type** type);

    // bool parseTemplateType(TemplateType** type, Name* name = 0);
    // ibool parseTemplateType(Type** type, Name* name = 0);
};

} // namespace vc

#endif // VC_PARSER_H_INCLUDE