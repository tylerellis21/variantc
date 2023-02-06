#include <vc/compiler/parser.h>

namespace vc {

bool Parser::parseStmt(Stmt* parentStmt, Stmt** out) {
    switch (current.kind) {

    case TokenKind::Semi: {
        // TODO(@Tyler): Better error message handling.
        std::cout << "Unexpected: " << current << std::endl;
        consume();
        return true;
    }

    case TokenKind::Case: return parseCaseStmt(parentStmt, out);
    case TokenKind::Continue: return parseContinueStmt(parentStmt, out);
    case TokenKind::Break: return parseBreakStmt(parentStmt, out);
    case TokenKind::Do: return parseDoStmt(parentStmt, out);
    case TokenKind::For: return parseForStmt(parentStmt, out);
    case TokenKind::If: return parseIfStmt(parentStmt, out);
    case TokenKind::Switch: return parseSwitchStmt(parentStmt, out);
    case TokenKind::While: return parseWhileStmt(parentStmt, out);
    case TokenKind::Goto: return parseGotoStmt(parentStmt, out);
    case TokenKind::Default: return parseDefaultStmt(parentStmt, out);
    case TokenKind::Return: return parseReturnStmt(parentStmt, out);
    case TokenKind::LBrace: return parseCompoundStmt(parentStmt, out);

    // A declaration inside of a statement
    case TokenKind::Def:
    case TokenKind::Struct:
    case TokenKind::Union: return parseDeclStmt(parentStmt, out);

    // Handle top level '(' in statements
    case TokenKind::LParen: {
        Expr* expr = parseParenExpr(parentStmt);
        if (!expr) return false;
        *out = expr;
        return true;
    }

    // TODO: Figure out what the using keyword will really do, if anything
    //case TokenKind::Using: return parse_decl_stmt(parent, out);

    // Is there a better way to test for this?

    // build a case for each TYPE_TOKEN.
    #define BUILTIN_KIND(NAME, TOKEN, SIZE) case TokenKind::##NAME:
    #include <vc/defs/builtin_kinds.inl>
    #undef BUILTIN_KIND
    // Fall through
    {
        if (!parseDeclStmt(parentStmt, out)) return false;
        return expectSemi();
    } break;

    case TokenKind::Star: {
        *out = parseAssignmentExpr(parentStmt);
        return expectSemi();
    }

    case TokenKind::Identifier: {

        // TODO: cleanup
        // perhaps combine this into a switch statement?

        // if (next.kind == TokenKind::Less) return parseTemplateStmt(parentStmt, out);

        if (next.kind == TokenKind::Colon) return parseLabelStmt(parentStmt, out);

        if (next.kind == TokenKind::LParen) {
            *out = parseCallExpr(parentStmt, true);
            return true;
        }

        if (next.kind == TokenKind::LSquare) {
            *out = parseAssignmentExpr(parentStmt);
            return true;
        }

        if (isOperatorKind(next.kind)) {
            *out = parseExpr(parentStmt);
            if (!expectSemi()) {
                printf(" statement\n");
                return false;
            }
            return true;
        }

        // TODO: Better handle this case when we have errors in statements.
        return parseDeclStmt(parentStmt, out);

    } break;

    default: break;

    } // switch (current.kind)

    if (next.kind == TokenKind::LSquare) {
        *out = parseAssignmentExpr(parentStmt);
        return true;
    }

    if (isOperatorKind(current.kind)) {
        *out = parseExpr(parentStmt);
        return expectSemi();
    }

    std::cout << "unexpected token in statement: " << current << std::endl;
    return false;
}

bool Parser::parseOptionalCompoundStmt(Stmt* parentStmt, Stmt** out) {
    if (current.kind == TokenKind::LBrace)
        return parseCompoundStmt(parentStmt, out);

    return parseStmt(parentStmt, out);
}

bool Parser::parseCompoundStmt(Stmt* parentStmt, Stmt** out) {

    SourceRange sourceRange = SourceRange::None;

    sourceRange.begin = loc();
    if (!expectConsume(TokenKind::LBrace)) return false;

    std::vector<Stmt*> statements;

    while (valid()) {
        if (current.kind == TokenKind::RBrace) break;

        Stmt* stmt = 0;
        if (!parseStmt(stmt, &stmt)) return false;

        statements.push_back(stmt);
    }

    sourceRange.end = loc();
    if (!expectConsume(TokenKind::RBrace)) return false;

    *out = new CompoundStmt(parentStmt, sourceRange, statements);
    return true;
}

bool Parser::parseContinueStmt(Stmt* parentStmt, Stmt** out) {
    SourceLocation sloc = loc();
    consume();
    if (expectSemi()) return false;
    *out = new ContinueStmt(parentStmt, sloc);
    return true;
}

bool Parser::parseBreakStmt(Stmt* parentStmt, Stmt** out) {
    SourceLocation sloc = loc();
    consume();
    if (!expectSemi()) return false;
    *out = new BreakStmt(parentStmt, sloc);
    return true;
}

bool Parser::parseTemplateStmt(Stmt* parentStmt, Stmt** out) {
/*
    WTF IS THIS DOING?!?

    struct Vector<T> {
        T x;
        T y;
    };
    //     TemplateDecl
    //      name T
    def add<T>(Vector<T> lhs, Vector<T> rhs) Vector<T> {
        //
        return Vector<T> {
            lhs.x + rhs.x,
            lhs.y + rhs.y
        };
    }

    typedef Vector<i32> v2i;
    typedef Vector<r32> v2f;

    v2f a = { 10.0f, 10.0f };
    v2f b = { 20.0f, 20.0f };
    v2f c = a + b;

    Vector<r32> aa = Vector<r32>::zero + add(a, b);

    def add(v2f lhs, v2f rhs) v2f {
        return v2f {
            lhs.x + rhs.x,
            lhs.y + rhs.y
        };
    }

    SourceLocation sloc = loc();

    TemplateType* templateType = 0;
    if (!parseTemplateType(&type)) return false;

    if (current.kind == TokenKind::LParen) {
        Expr* expr = parseCallExpr(
            parentStmt,
            true,
            templateType,
            template_type
        );
        expr->parentStmt = parentStmt;
        *out = expr;
        return true;
    }
    else {
        DeclGroup* dg = new DeclGroup(0);
        DeclStmt* decl_stmt = new DeclStmt(start_loc, parentStmt, dg);

        if (!parse_compound_var_decl(0, dg, template_type)) return false;

        *out = decl_stmt;
        return expect_semi();
    }
*/
    return false;
}

bool Parser::parseDeclStmt(Stmt* parentStmt, Stmt** out) {
    SourceLocation sloc = loc();
    DeclGroup* declGroup = new DeclGroup(0);
    if (!parseDecl(0, declGroup)) return false;
    *out = new DeclStmt(parentStmt, sloc, declGroup);
    return true;
}

// do { block; } while(condition_expr) { block }
// do stmt; while(condition_expr) stmt;
bool Parser::parseDoStmt(Stmt* parentStmt, Stmt** out) {
    SourceLocation sloc = consume();
    Stmt* bodyStmt = 0;
    Stmt* whileStmt = 0;
    if (!parseOptionalCompoundStmt(parentStmt, &bodyStmt)) return false;
    if (!parseWhileStmt(parentStmt, &whileStmt)) return false;
    *out = new DoStmt(parentStmt, sloc, bodyStmt, whileStmt);
    return true;
}

// for (init, condition, increment) body;
bool Parser::parseForStmt(Stmt* parentStmt, Stmt** out) {
    SourceLocation keywordLoc = consume();
    Stmt* initStmt = 0;
    Expr* conditionStmt = 0;
    Expr* incrementStmt = 0;
    Stmt* bodyStmt = 0;

    SourceRange braceRange;
    braceRange.begin = loc();
    if (!expectConsume(TokenKind::LParen)) return false;

    // initalizer
    if (!parseStmt(0, &initStmt)) return false;

    conditionStmt = parseExpr(0);

    if (!expectSemi()) return false;

    incrementStmt = parseExpr(parentStmt);

    braceRange.end = loc();
    if (!expectConsume(TokenKind::RParen)) return false;

    if (!parseOptionalCompoundStmt(0, &bodyStmt)) return false;

    ForStmt* forStmt = new ForStmt(
        parentStmt,
        keywordLoc,
        braceRange,
        initStmt,
        conditionStmt,
        incrementStmt,
        bodyStmt
    );

    // TODO(@Tyler): I don't think having to do this :(
    setStmtParent(forStmt->initStmt, forStmt);
    setStmtParent(forStmt->conditionStmt, forStmt);
    setStmtParent(forStmt->incrementStmt, forStmt);
    setStmtParent(forStmt->bodyStmt, forStmt);

    *out = forStmt;

    return true;
}

bool Parser::parseIfStmt(Stmt* parentStmt, Stmt** out) {
    SourceLocation keywordLoc = loc();

    if (!expectConsume(TokenKind::If)) return false;

    SourceRange sourceRange;
    Expr* conditionStmt = 0;
    Stmt* bodyStmt = 0;
    Stmt* elseStmt = 0;

    sourceRange.begin = loc();
    if (!expectConsume(TokenKind::LParen)) return false;

    conditionStmt = parseExpr(0);

    sourceRange.end = loc();
    if (!expectConsume(TokenKind::RParen)) return false;

    if (!parseOptionalCompoundStmt(0, &bodyStmt)) return false;

    if (current.kind == TokenKind::Else) {
        consume();
        if (!parseOptionalCompoundStmt(0, &elseStmt)) return false;
    }

    IfStmt* ifStmt = new IfStmt(
        parentStmt,
        keywordLoc,
        sourceRange,
        conditionStmt,
        bodyStmt,
        elseStmt
    );

    setStmtParent(ifStmt->conditionStmt, ifStmt);
    setStmtParent(ifStmt->bodyStmt, ifStmt);
    setStmtParent(ifStmt->elseStmt, ifStmt);

    *out = ifStmt;

    return true;
}

bool Parser::parseLabelStmt(Stmt* parentStmt, Stmt** out) {
    SourceLocation sloc = loc();
    Name name;
    if (!parseName(&name, false)) return false;

    if (!expectConsume(TokenKind::Colon)) return false;

    *out = new LabelStmt(
        parentStmt,
        sloc,
        name
    );

    return true;
}

bool Parser::parseGotoStmt(Stmt* parentStmt, Stmt** out) {
    SourceLocation loc = consume();
    Name name;

    if (!parseName(&name, false)) return false;
    if (!expectSemi()) return false;

    *out = new GotoStmt(
        parentStmt,
        loc,
        name
    );

    return true;
}

// switch(expr) { body; }
bool Parser::parseSwitchStmt(Stmt* parentStmt, Stmt** out) {
    SourceLocation keywordLoc = consume();

    Expr* conditionExpr = 0;
    Stmt* bodyStmt = 0;

    SourceRange sourceRange = SourceRange::None;

    sourceRange.begin = loc();
    if (!expectConsume(TokenKind::LParen)) return false;

    conditionExpr = parseAssignmentExpr(0);

    sourceRange.end = loc();
    if (!expectConsume(TokenKind::RParen)) return false;

    if (!parseCompoundStmt(0, &bodyStmt)) return false;

    SwitchStmt* switchStmt = new SwitchStmt(
        parentStmt,
        keywordLoc,
        sourceRange,
        conditionExpr,
        bodyStmt
    );

    setStmtParent(switchStmt->conditionExpr, switchStmt);
    setStmtParent(switchStmt->bodyStmt, switchStmt);

    *out = switchStmt;

    return true;
}

bool Parser::parseCaseStmt(Stmt* parentStmt, Stmt** out) {

    SourceLocation keywordLoc = loc();
    if (!expectConsume(TokenKind::Case)) return false;

    Expr* valueExpr = parseExpr(0);

    if (!expectConsume(TokenKind::Colon)) return false;

    Stmt* bodyStmt = 0;
    if (!parseStmt(0, &bodyStmt)) return false;

    CaseStmt* caseStmt = new CaseStmt(
        parentStmt,
        keywordLoc,
        valueExpr,
        bodyStmt
    );

    setStmtParent(caseStmt->valueExpr, caseStmt);
    setStmtParent(caseStmt->bodyStmt, caseStmt);

    *out = caseStmt;

    return true;
}

bool Parser::parseDefaultStmt(Stmt* parentStmt, Stmt** out) {
    SourceLocation keywordLoc = loc();
    if (!expectConsume(TokenKind::Default)) return false;
    if (!expectConsume(TokenKind::Colon)) return false;


    Stmt* bodyStmt = 0;
    if (!parseStmt(0, &bodyStmt)) return false;

    DefaultStmt* defaultStmt = new DefaultStmt(
        parentStmt,
        keywordLoc,
        bodyStmt
    );

    setStmtParent(defaultStmt->bodyStmt, defaultStmt);

    *out = defaultStmt;
    return true;
}

bool Parser::parseReturnStmt(Stmt* parentStmt, Stmt** out) {

    SourceLocation keywordLoc = loc();
    if (!expectConsume(TokenKind::Return)) return false;

    Expr* expr = parseExpr(0);
    if (!expectSemi()) {
        printf("in return statement\n");
        return false;
    }

    ReturnStmt* returnStmt = new ReturnStmt(
        parentStmt,
        keywordLoc,
        expr
    );

    returnStmt->expr = expr;
    *out = returnStmt;

    return true;
}

bool Parser::parseWhileStmt(Stmt* parentStmt, Stmt** out) {
    SourceLocation loc = consume();
    Expr* condition = 0;
    Stmt* body = 0;

    SourceRange sourceRange = SourceRange::None;

    if (!expect_consume(TokenKind::LParen)) return false;
    condition = parse_expr(stmt);

    if (!expect_consume(TokenKind::RParen)) return false;

    if (current.kind == TokenKind::Semi) consume();
    else
        if (!parse_optional_compound_stmt(parentStmt, &body)) return false;

    WhileStmt* whileStmt = new WhileStmt(
        parentStmt,
        loc,
        condition,
        body
    );

    setStmtParent(whileStmt->conditionExpr, whileStmt);
    setStmtParent(whileStmt->bodyStmt, whileStmt);

    *out = whileStmt;

    return true;
}

} // namespace vc