#include <vc/compiler/parser.h>

namespace vc {

Expr* Parser::expr_error() {
    consume();
    failed = true;
    return 0;
}

Expr* Parser::parse_expr(Stmt* stmt_parent) {
    Expr* lhs = parse_assignment_expr(stmt_parent);
    return parse_rhs_binary_op(stmt_parent, lhs, prec::Comma);
}

Expr* Parser::parse_assignment_expr(Stmt* stmt_parent) {
    Expr* lhs = parse_cast_expr(stmt_parent);
    return parse_rhs_binary_op(stmt_parent, lhs, prec::Assignment);
}

Expr* Parser::parse_rhs_binary_op(Stmt* stmt_parent, Expr* lhs, i32 min_precedence) {
    prec::Level next_op_prec = token_precedence(current.kind);

    while (1) {
        if (next_op_prec < min_precedence) break;
        Token op_token = current;
        consume();

        if (next_op_prec == prec::Conditional) {
            lhs = parse_ternary_expr(stmt_parent, lhs);
            break;
        }

        Expr* rhs = 0;
        if (next_op_prec <= prec::Conditional)
            rhs = parse_assignment_expr(stmt_parent);
        else
            rhs = parse_cast_expr(stmt_parent);

        prec::Level this_prec = next_op_prec;
        next_op_prec = token_precedence(current.kind);

        bool is_right_assoc = this_prec == prec::Conditional
                || this_prec == prec::Assignment;

        if (this_prec < next_op_prec
                || ((this_prec == next_op_prec) && is_right_assoc)) {
            rhs = parse_rhs_binary_op(stmt_parent, rhs, this_prec + !is_right_assoc);
            next_op_prec = token_precedence(current.kind);
        }

        lhs = new BinaryOpExpr(op_token.loc, lhs, rhs, op_token.kind, stmt_parent);
    }

    return lhs;
}

Expr* Parser::parse_cast_expr(Stmt* stmt_parent) {
    Expr* result = 0;

    switch (current.kind) {
    default: return 0;
    case TokenKind::BooleanLiteral:
    case TokenKind::CharacterLiteral:
    case TokenKind::IntegerLiteral:
    case TokenKind::RealLiteral:
    case TokenKind::StringLiteral:
        result = parse_literal_expr(stmt_parent);
        break;

    case TokenKind::Cast: {
        SourceLocation sloc = consume();
        if (!expect_consume(TokenKind::Less)) return 0;

        Type* type = 0;
        if (!parse_type(&type)) return 0;

        if (!expect_consume(TokenKind::Greater)) return 0;

        Expr* expr = parse_cast_expr(stmt_parent);
        result = new CastExpr(sloc, type, expr, stmt_parent);

    } break;

    case TokenKind::Identifier: {
        if (ahead.kind == TokenKind::LParen ||
            ahead.kind == TokenKind::At) {
            result = parse_call_expr(stmt_parent, false);
        }
        else if (ahead.kind == TokenKind::Period) {
            result = parse_member_expr(stmt_parent);
        }
        else
            result = parse_decl_ref_expr(stmt_parent);
    } break;

    case TokenKind::Equal: {
        consume();
        result = parse_assignment_expr(stmt_parent);
    } break;

    case TokenKind::LParen: {
        result = parse_paren_expr(stmt_parent);
    } break;

    case TokenKind::Amp:
    case TokenKind::Star:
    case TokenKind::Exclaim:
    case TokenKind::Tilde:
    case TokenKind::Minus:
    case TokenKind::MinusMinus:
    case TokenKind::PlusPlus:
    case TokenKind::LSquare: {
        result = parse_postfix_expr(stmt_parent, result, false);
    } break;

    case TokenKind::LBrace: {
        result = parse_initalizer_expr(stmt_parent);
    } break;

    } // switch (parser->current.kind)

    switch (current.kind) {
    default: break;
    case TokenKind::PlusPlus:
    case TokenKind::MinusMinus:
    case TokenKind::LSquare: {
        result = parse_postfix_expr(stmt_parent, result, true);
    } break;
    }

    return result;
}

Expr* Parser::parse_ternary_expr(Stmt* stmt_parent, Expr* condition) {
    SourceLocation sloc = loc();
    Expr* lhs = parse_cast_expr(stmt_parent);
    if (!expect_consume(TokenKind::Colon)) return 0;
    Expr* rhs = parse_cast_expr(stmt_parent);
    return new TernaryExpr(sloc, condition, lhs, rhs, stmt_parent);
}

Expr* Parser::parse_initalizer_expr(Stmt* stmt_parent) {
    SourceLocation sloc = loc();
    List<Expr*> values(1);

    if (!expect_consume(TokenKind::LBrace)) return 0;
    while (valid()) {
        if (current.kind == TokenKind::RBrace) return 0;
        Expr* value = parse_assignment_expr(stmt_parent);
        values.push(value);
        if (current.kind == TokenKind::Comma) {
            consume();
            continue;
        } else break;
    }
    if (!expect_consume(TokenKind::RBrace)) return 0;
    return new InitalizerExpr(sloc, values, stmt_parent);
}

Expr* Parser::parse_array_subscript_expr(Stmt* stmt_parent, Expr* lhs) {
    SourceLocation sloc = loc();
    if (!expect_consume(TokenKind::LSquare)) return 0;
    Expr* rhs = parse_cast_expr(stmt_parent);
    if (!expect_consume(TokenKind::RSquare)) return 0;
    return new ArraySubscriptExpr(sloc, lhs, rhs, stmt_parent);
}

Expr* Parser::parse_unary_expr(Stmt* stmt_parent, Expr* lhs, bool postfix) {
    Token op = current;
    consume();
    Expr* expr = lhs ? lhs : parse_cast_expr(stmt_parent);
    return new UnaryOpExpr(op.loc, expr, op.kind, postfix, stmt_parent);
}

Expr* Parser::parse_postfix_expr(Stmt* stmt_parent, Expr* lhs, bool postfix) {
    switch(current.kind) {
    default: return 0;
    case TokenKind::Amp:
    case TokenKind::Exclaim:
    case TokenKind::Star:
    case TokenKind::Tilde:
    case TokenKind::Minus:
    case TokenKind::MinusMinus:
    case TokenKind::PlusPlus: return parse_unary_expr(stmt_parent, lhs, postfix);
    case TokenKind::LSquare: return parse_array_subscript_expr(stmt_parent, lhs);
    }
}

Expr* Parser::parse_decl_ref_expr(Stmt* stmt_parent) {
    SourceLocation sloc = loc();
    if (!expect_kind(TokenKind::Identifier)) return expr_error();

    Name* name = 0;
    if (!parse_name(&name, true)) return expr_error();

    return new DeclRefExpr(sloc, name, 0, 0, stmt_parent);
}

Expr* Parser::parse_literal_expr(Stmt* stmt_parent) {
    SourceLocation sloc = loc();
    Token token = current;
    consume();

    Expr* result = 0;

    switch (token.kind) {

    case TokenKind::BooleanLiteral: {
        bool value;
        if (token.str.compare("true") == 0)
            value = true;
        else
            value = false;
        result = new BooleanLiteral(sloc, value, stmt_parent);
    } break;

    case TokenKind::CharacterLiteral: {

        u64 length = utf8_sequence_length(token.str.buffer[0]);
        rune value = utf8_decode_rune(token.str.buffer, length);

        result = new CharLiteral(token.loc, value, stmt_parent);
    } break;

    case TokenKind::StringLiteral: {
        result = new StringLiteral(token.loc, token.str, stmt_parent);
    } break;

    case TokenKind::IntegerLiteral: {
        // TODO: Figure out the proper integer type.
        //bool is_signed = token.str[0] == '-';
        i64 value = atoll((char*)token.str.buffer);
        result = new IntegerLiteral(token.loc, value, stmt_parent);
    } break;

    case TokenKind::RealLiteral: {
        r64 value = atof((char*)token.str.buffer);
        result = new RealLiteral(token.loc, value, stmt_parent);
    } break;

    default: {
        result = expr_error();
        printf("unhandled literal type\n");
    } break;

    } // switch (token.kind)
    return result;
}

Expr* Parser::parse_paren_expr(Stmt* stmt_parent) {
    SourceLocation lparen_loc = loc();
    consume();

    Expr* expr = parse_expr(stmt_parent);

    SourceLocation rparen_loc = loc();
    if (!expect_consume(TokenKind::RParen)) return expr_error();

    return new ParenExpr(lparen_loc, lparen_loc, rparen_loc, expr, stmt_parent);
}

Expr* Parser::parse_member_expr(Stmt* stmt_parent) {

    SourceLocation sloc = loc();

    Name* name = 0;
    if (!parse_name(&name, true)) return 0;

    if (!expect_consume(TokenKind::Period)) return 0;

    Expr* expr = parse_cast_expr(stmt_parent);

    return new MemberExpr(sloc, name, expr, 0, stmt_parent);
}

Expr* Parser::parse_call_expr(
    Stmt* stmt_parent,
    bool expect_semi,
    Name* name,
    Type* template_type) {

    SourceLocation sloc = loc();
    List<Expr*> args(1);

    if (ahead.kind == TokenKind::At) {
        if (!parse_template_type(&template_type)) return expr_error();
    }
    else if (!name)
         if (!parse_name(&name, true)) return 0;

    if (!expect_consume(TokenKind::LParen)) return 0;

    while (valid()) {
        if (current.kind == TokenKind::RParen) break;
        Expr* expr = parse_assignment_expr(stmt_parent);
        args.push(expr);
        if (current.kind == TokenKind::Comma) {
            consume();
            continue;
        } else break;
    }

    if (!expect_consume(TokenKind::RParen)) return 0;
    if (expect_semi)
        if (!this->expect_semi()) return expr_error();

    return new CallExpr(sloc, name, 0, template_type, args, stmt_parent);
}

} // namespace vc

