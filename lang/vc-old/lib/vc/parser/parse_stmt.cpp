#include <vc/parser.h>

namespace t {
namespace vc {

bool Parser::parse_stmt(Stmt* stmt_parent, Stmt** out) {
    switch (current.kind) {

    case TokenKind::Semi: {
        consume();
        return true;
    }

    case TokenKind::Case: return parse_case_stmt(stmt_parent, out);
    case TokenKind::Continue: return parse_continue_stmt(stmt_parent, out);
    case TokenKind::Break: return parse_break_stmt(stmt_parent, out);
    case TokenKind::Do: return parse_do_stmt(stmt_parent, out);
    case TokenKind::For: return parse_for_stmt(stmt_parent, out);
    case TokenKind::If: return parse_if_stmt(stmt_parent, out);
    case TokenKind::Switch: return parse_switch_stmt(stmt_parent, out);
    case TokenKind::While: return parse_while_stmt(stmt_parent, out);
    case TokenKind::Goto: return parse_goto_stmt(stmt_parent, out);
    case TokenKind::Default: return parse_default_stmt(stmt_parent, out);
    case TokenKind::Return: return parse_return_stmt(stmt_parent, out);
    case TokenKind::LBrace: return parse_compound_stmt(stmt_parent, out);

    // A declaration inside of a statement
    case TokenKind::Struct:
    case TokenKind::Union: return parse_decl_stmt(stmt_parent, out);

    // Handle top level '(' in statements
    case TokenKind::LParen: {
        Expr* expr = parse_paren_expr(stmt_parent);
        if (!expr) return false;
        *out = expr;
        return true;
    }

    // TODO: Figure out what the using keyword will really do, if anything
    //case TokenKind::Using: return parse_decl_stmt(parent, out);

#define TYPE_TOKEN(TOKEN) case TokenKind::TOKEN:
    TYPE_TOKENS
#undef TYPE_TOKEN
        return parse_decl_stmt(stmt_parent, out);

    case TokenKind::Star: {
        *out = parse_assignment_expr(stmt_parent);
        return expect_semi();
    }

    case TokenKind::Def: return parse_decl_stmt(stmt_parent, out);

    case TokenKind::Identifier: {

        // TODO: cleanup
        // perhaps combine this into a switch statement?

        if (ahead.kind == TokenKind::At) return parse_template_stmt(stmt_parent, out);

        if (ahead.kind == TokenKind::Colon) return parse_label_stmt(stmt_parent, out);

        if (ahead.kind == TokenKind::LParen) {
            *out = parse_call_expr(stmt_parent, true);
            return true;
        }

        if (ahead.kind == TokenKind::LSquare) {
            *out = parse_assignment_expr(stmt_parent);
            return true;
        }

        if (token_is_operator(ahead.kind)) {
            *out = parse_expr(stmt_parent);
            if (!expect_semi()) {
                printf(" statement\n");
                return false;
            }
            return true;
        }

        // TODO: Better handle this case when we have errors in statements.
        return parse_decl_stmt(stmt_parent, out);

    } break;

    default: break;

    } // switch (current.kind)

    if (ahead.kind == TokenKind::LSquare) {
        *out = parse_assignment_expr(stmt_parent);
        return true;
    }

    if (token_is_operator(current.kind)) {
        *out = parse_expr(stmt_parent);
        return expect_semi();
    }

    token_print(&current);
    printf("unexpected token in statement: ");
    return false;
}

bool Parser::parse_optional_compound_stmt(Stmt* stmt_parent, Stmt** out) {
    if (current.kind == TokenKind::LBrace) return parse_compound_stmt(stmt_parent, out);
    return parse_stmt(stmt_parent, out);
}

bool Parser::parse_compound_stmt(Stmt* stmt_parent, Stmt** out) {

    CompoundStmt* stmt = new CompoundStmt(loc(), stmt_parent);

    SourceLocation lbrace_loc = loc();
    if (!expect_consume(TokenKind::LBrace)) return false;

    List<Stmt*> statements(1);

    while (valid()) {
        if (current.kind == TokenKind::RBrace) break;

        Stmt* sub_stmt = 0;
        if (!parse_stmt(stmt, &sub_stmt)) return false;

        statements.push(sub_stmt);
    }

    SourceLocation rbrace_loc = loc();
    if (!expect_consume(TokenKind::RBrace)) return false;

    stmt->lbrace_loc = lbrace_loc;
    stmt->rbrace_loc = rbrace_loc;
    stmt->statements = statements;

    *out = stmt;
    return true;
}

bool Parser::parse_continue_stmt(Stmt* parent, Stmt** out) {
    SourceLocation sloc = loc();
    consume();
    if (expect_semi()) return false;
    *out = new ContinueStmt(sloc, parent);
    return true;
}

bool Parser::parse_break_stmt(Stmt* parent, Stmt** out) {
    SourceLocation sloc = loc();
    consume();
    if (!expect_semi()) return false;
    *out = new BreakStmt(sloc, parent);
    return true;
}

bool Parser::parse_template_stmt(Stmt* stmt_parent, Stmt** out) {

    SourceLocation start_loc = loc();

    Type* type = 0;
    if (!parse_type(&type)) return false;

    //@Tyler HMM
    TemplateType* template_type = static_cast<TemplateType*>(type);

    if (current.kind == TokenKind::LParen) {
        Expr* expr = parse_call_expr(stmt_parent,
                                     true,
                                     template_type->name,
                                     template_type);
        expr->stmt_parent = stmt_parent;
        *out = expr;
        return true;
    }
    else {
        DeclGroup* dg = new DeclGroup(0);
        DeclStmt* decl_stmt = new DeclStmt(start_loc, stmt_parent, dg);

        if (!parse_compound_var_decl(0, dg, template_type)) return false;

        *out = decl_stmt;
        return expect_semi();
    }

    return true;
}

bool Parser::parse_decl_stmt(Stmt* stmt_parent, Stmt** out) {
    SourceLocation sloc = loc();
    DeclGroup* dg = new DeclGroup(0);
    if (!parse_top_level_decl(0, dg)) return false;
    *out = new DeclStmt(sloc, stmt_parent, dg);
    return true;
}

// do { block; } while(condition_expr) { block }
// do stmt; while(condition_expr) stmt;
bool Parser::parse_do_stmt(Stmt* stmt_parent, Stmt** out) {
    SourceLocation sloc = consume();
    Stmt* body = 0;
    Stmt* while_stmt = 0;
    if (!parse_optional_compound_stmt(stmt_parent, &body)) return false;
    if (!parse_while_stmt(stmt_parent, &while_stmt)) return false;
    *out = new DoStmt(sloc, stmt_parent, body, while_stmt);
    return true;
}

// for (init, condition, increment) body;
bool Parser::parse_for_stmt(Stmt* stmt_parent, Stmt** out) {
    SourceLocation sloc = consume();
    Stmt* init_stmt = 0;
    Expr* condition = 0;
    Expr* increment = 0;
    Stmt* body = 0;

    ForStmt* for_stmt = new ForStmt(sloc, stmt_parent, 0, 0, 0, 0);

    if (!expect_consume(TokenKind::LParen)) return false;

    // initalizer
    if (!parse_stmt(stmt_parent, &init_stmt)) return false;

    condition = parse_expr(stmt_parent);

    if (!expect_semi()) return false;

    increment = parse_expr(stmt_parent);

    if (!expect_consume(TokenKind::RParen)) return false;

    if (!parse_optional_compound_stmt(for_stmt, &body)) return false;

    for_stmt->init = init_stmt;
    for_stmt->condition = condition;
    for_stmt->inc = increment;
    for_stmt->body = body;

    *out = for_stmt;

    return true;
}

bool Parser::parse_if_stmt(Stmt* stmt_parent, Stmt** out) {
    SourceLocation sloc = loc();
    if (!expect_consume(TokenKind::If)) return false;

    IfStmt* stmt = new IfStmt(sloc, stmt_parent, 0, 0, 0);

    SourceLocation lparen_loc;
    SourceLocation rparen_loc;
    Expr* condition = 0;

    {
        lparen_loc = loc();
        if (!expect_consume(TokenKind::LParen)) return false;

        condition = parse_expr(stmt_parent);

        rparen_loc = loc();
        if (!expect_consume(TokenKind::RParen)) return false;
    }

    Stmt* body = 0;
    Stmt* else_stmt = 0;

    {
        if (!parse_optional_compound_stmt(stmt_parent, &body)) return false;
        if (current.kind == TokenKind::Else) {
            consume();
            if (!parse_optional_compound_stmt(stmt_parent, &else_stmt)) return false;
        }
    }

    stmt->body = body;
    stmt->condition = condition;
    stmt->else_stmt = else_stmt;

    *out = stmt;
    return true;
}

bool Parser::parse_label_stmt(Stmt* parent, Stmt** out) {
    SourceLocation sloc = loc();
    Name* label_name = 0;
    if (!parse_name(&label_name, false)) return false;
    if (!expect_consume(TokenKind::Colon)) return false;
    *out = new LabelStmt(sloc, parent, label_name);
    return true;
}

bool Parser::parse_goto_stmt(Stmt* parent, Stmt** out) {
    SourceLocation loc = consume();
    Name* label_name = 0;
    if (!parse_name(&label_name, false)) return false;
    if (!expect_semi()) return false;
    *out = new GotoStmt(loc, parent, label_name, 0);
    return true;
}

// switch(expr) { body; }
bool Parser::parse_switch_stmt(Stmt* stmt_parent, Stmt** out) {
    SourceLocation sloc = consume();
    SwitchStmt* stmt = new SwitchStmt(sloc, stmt_parent, 0, 0);
    SourceLocation lparen_loc = loc();

    if (!expect_consume(TokenKind::LParen)) return false;

    Expr* value = parse_assignment_expr(stmt);
    SourceLocation rparen_loc = loc();

    if (!expect_consume(TokenKind::RParen)) return false;
    if (!parse_compound_stmt(stmt_parent, &stmt->body)) return false;

    stmt->value = value;
    stmt->lparen_loc = lparen_loc;
    stmt->rparen_loc = rparen_loc;

    *out = stmt;
    return true;
}

bool Parser::parse_case_stmt(Stmt* stmt_parent, Stmt** out) {

    SourceLocation sloc = loc();
    if (!expect_consume(TokenKind::Case)) return false;

    CaseStmt* stmt = new CaseStmt(sloc, stmt_parent, 0, 0);

    Expr* value = parse_expr(stmt_parent);

    if (!expect_consume(TokenKind::Colon)) return false;

    Stmt* sub_stmt = 0;
    if (!parse_stmt(stmt, &sub_stmt)) return false;

    stmt->value = value;
    stmt->stmt = sub_stmt;

    *out = stmt;

    return true;
}

bool Parser::parse_default_stmt(Stmt* stmt_parent, Stmt** out) {
    SourceLocation sloc = loc();
    if (!expect_consume(TokenKind::Default)) return false;
    if (!expect_consume(TokenKind::Colon)) return false;

    DefaultStmt* stmt = new DefaultStmt(sloc, stmt_parent, 0);

    Stmt* sub_stmt = 0;
    if (!parse_stmt(stmt_parent, &sub_stmt)) return false;

    stmt->stmt = sub_stmt;

    *out = stmt;
    return true;
}

bool Parser::parse_return_stmt(Stmt* stmt_parent, Stmt** out) {

    SourceLocation sloc = loc();
    if (!expect_consume(TokenKind::Return)) return false;

    ReturnStmt* stmt = new ReturnStmt(sloc, stmt_parent, 0);

    Expr* expr = parse_expr(stmt_parent);

    if (!expect_semi()) {
        printf(" return statement\n");
        return false;
    }

    stmt->expr = expr;
    *out = stmt;

    return true;
}

bool Parser::parse_while_stmt(Stmt* stmt_parent, Stmt** out) {
    SourceLocation loc = consume();
    Expr* condition = 0;
    Stmt* body = 0;
    WhileStmt* stmt = new WhileStmt(loc, stmt_parent, 0, 0);

    if (!expect_consume(TokenKind::LParen)) return false;
    condition = parse_expr(stmt);
    if (!expect_consume(TokenKind::RParen)) return false;

    if (current.kind == TokenKind::Semi) consume();
    else
        if (!parse_optional_compound_stmt(stmt_parent, &body)) return false;

    stmt->body = body;
    stmt->condition = condition;

    *out = stmt;

    return true;
}

} // namespace vc
} // namespace t
