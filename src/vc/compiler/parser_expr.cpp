#include <vc/compiler/parser.h>
#include <vc/basic/tokenprecedence.h>

namespace vc {

Expr* Parser::exprError() {
    consume();
    return 0;
}

Expr* Parser::parseExpr(Stmt* parentStmt) {
    Expr* lhs = parseAssignmentExpr(parentStmt);
    return parseRhsBinaryOp(parentStmt, lhs, prec::Comma);
}

Expr* Parser::parseAssignmentExpr(Stmt* parentStmt) {
    Expr* lhs = parseCastExpr(parentStmt);
    return parseRhsBinaryOp(parentStmt, lhs, TokenPrecedence::Assignment);
}

Expr* Parser::parseRhsBinaryOp(Stmt* parentStmt, Expr* lhs, i32 minPrecedence) {
    TokenPrecedence nextOperatorPrec = getTokenPrecedence(current.kind);

    while (1) {
        if (nextOperatorPrec < minPrecedence) break;
        Token opToken = current;
        consume();

        if (nextOperatorPrec == prec::Conditional) {
            lhs = parseTernaryExpr(parentStmt, lhs);
            break;
        }

        Expr* rhs = 0;
        if (nextOperatorPrec <= prec::Conditional)
            rhs = parseAssignmentExpr(parentStmt);
        else
            rhs = parseCastExpr(parentStmt);

        TokenPrecedence currentTokenPrec = nextOperatorPrec;
        nextOperatorPrec = getTokenPrecedence(current.kind);

        bool isRightAssoc = currentTokenPrec == prec::Conditional|| currentTokenPrec == prec::Assignment;

        if (currentTokenPrec < nextOperatorPrec || ((currentTokenPrec == nextOperatorPrec) && isRightAssoc)) {
            rhs = parseRhsBinaryOp(parentStmt, rhs, currentTokenPrec + !isRightAssoc);
            nextOperatorPrec = getTokenPrecedence(current.kind);
        }

        lhs = new BinaryOpExpr(
            parentStmt,
            opToken.loc,
            lhs,
            rhs,
            opToken.kind
        );
    }

    return lhs;
}

Expr* Parser::parseCastExpr(Stmt* parentStmt) {
    Expr* result = 0;

    switch (current.kind) {
    default: return 0;
    case TokenKind::BooleanLiteral:
    case TokenKind::CharacterLiteral:
    case TokenKind::IntegerLiteral:
    case TokenKind::RealLiteral:
    case TokenKind::StringLiteral:
        result = parseLiteralExpr(parentStmt);
        break;

    case TokenKind::Cast: {
        SourceLocation sloc = consume();
        if (!expectConsume(TokenKind::Less)) return 0;

        Type* type = 0;
        if (!parseType(&type)) return 0;

        if (!expectConsume(TokenKind::Greater)) return 0;

        Expr* expr = parseCastExpr(parentStmt);
        result = new CastExpr(parentStmt, sloc, expr, type);
    } break;

    case TokenKind::Identifier: {
        if (ahead.kind == TokenKind::LParen ||
            ahead.kind == TokenKind::At) {
            result = parse_call_expr(parentStmt, false);
        }
        else if (ahead.kind == TokenKind::Period) {
            result = parse_member_expr(parentStmt);
        }
        else
            result = parse_decl_ref_expr(parentStmt);
    } break;

    case TokenKind::Equal: {
        consume();
        result = parse_assignment_expr(parentStmt);
    } break;

    case TokenKind::LParen: {
        result = parse_paren_expr(parentStmt);
    } break;

    case TokenKind::Amp:
    case TokenKind::Star:
    case TokenKind::Exclaim:
    case TokenKind::Tilde:
    case TokenKind::Minus:
    case TokenKind::MinusMinus:
    case TokenKind::PlusPlus:
    case TokenKind::LSquare: {
        result = parse_postfix_expr(parentStmt, result, false);
    } break;

    case TokenKind::LBrace: {
        result = parse_initalizer_expr(parentStmt);
    } break;

    } // switch (parser->current.kind)

    switch (current.kind) {
    default: break;
    case TokenKind::PlusPlus:
    case TokenKind::MinusMinus:
    case TokenKind::LSquare: {
        result = parse_postfix_expr(parentStmt, result, true);
    } break;
    }

    return result;
}

Expr* Parser::parse_ternary_expr(Stmt* parentStmt, Expr* condition) {
    SourceLocation sloc = loc();
    Expr* lhs = parse_cast_expr(parentStmt);
    if (!expect_consume(TokenKind::Colon)) return 0;
    Expr* rhs = parse_cast_expr(parentStmt);
    return new TernaryExpr(sloc, condition, lhs, rhs, parentStmt);
}

Expr* Parser::parse_initalizer_expr(Stmt* parentStmt) {
    SourceLocation sloc = loc();
    List<Expr*> values(1);

    if (!expect_consume(TokenKind::LBrace)) return 0;
    while (valid()) {
        if (current.kind == TokenKind::RBrace) return 0;
        Expr* value = parse_assignment_expr(parentStmt);
        values.push(value);
        if (current.kind == TokenKind::Comma) {
            consume();
            continue;
        } else break;
    }
    if (!expect_consume(TokenKind::RBrace)) return 0;
    return new InitalizerExpr(sloc, values, parentStmt);
}

Expr* Parser::parse_array_subscript_expr(Stmt* parentStmt, Expr* lhs) {
    SourceLocation sloc = loc();
    if (!expect_consume(TokenKind::LSquare)) return 0;
    Expr* rhs = parse_cast_expr(parentStmt);
    if (!expect_consume(TokenKind::RSquare)) return 0;
    return new ArraySubscriptExpr(sloc, lhs, rhs, parentStmt);
}

Expr* Parser::parse_unary_expr(Stmt* parentStmt, Expr* lhs, bool postfix) {
    Token op = current;
    consume();
    Expr* expr = lhs ? lhs : parse_cast_expr(parentStmt);
    return new UnaryOpExpr(op.loc, expr, op.kind, postfix, parentStmt);
}

Expr* Parser::parse_postfix_expr(Stmt* parentStmt, Expr* lhs, bool postfix) {
    switch(current.kind) {
    default: return 0;
    case TokenKind::Amp:
    case TokenKind::Exclaim:
    case TokenKind::Star:
    case TokenKind::Tilde:
    case TokenKind::Minus:
    case TokenKind::MinusMinus:
    case TokenKind::PlusPlus: return parse_unary_expr(parentStmt, lhs, postfix);
    case TokenKind::LSquare: return parse_array_subscript_expr(parentStmt, lhs);
    }
}

Expr* Parser::parse_decl_ref_expr(Stmt* parentStmt) {
    SourceLocation sloc = loc();
    if (!expect_kind(TokenKind::Identifier)) return expr_error();

    Name* name = 0;
    if (!parse_name(&name, true)) return expr_error();

    return new DeclRefExpr(sloc, name, 0, 0, parentStmt);
}

Expr* Parser::parse_literal_expr(Stmt* parentStmt) {
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
        result = new BooleanLiteral(sloc, value, parentStmt);
    } break;

    case TokenKind::CharacterLiteral: {

        u64 length = utf8_sequence_length(token.str.buffer[0]);
        rune value = utf8_decode_rune(token.str.buffer, length);

        result = new CharLiteral(token.loc, value, parentStmt);
    } break;

    case TokenKind::StringLiteral: {
        result = new StringLiteral(token.loc, token.str, parentStmt);
    } break;

    case TokenKind::IntegerLiteral: {
        // TODO: Figure out the proper integer type.
        //bool is_signed = token.str[0] == '-';
        i64 value = atoll((char*)token.str.buffer);
        result = new IntegerLiteral(token.loc, value, parentStmt);
    } break;

    case TokenKind::RealLiteral: {
        r64 value = atof((char*)token.str.buffer);
        result = new RealLiteral(token.loc, value, parentStmt);
    } break;

    default: {
        result = expr_error();
        printf("unhandled literal type\n");
    } break;

    } // switch (token.kind)
    return result;
}

Expr* Parser::parse_paren_expr(Stmt* parentStmt) {
    SourceLocation lparen_loc = loc();
    consume();

    Expr* expr = parse_expr(parentStmt);

    SourceLocation rparen_loc = loc();
    if (!expect_consume(TokenKind::RParen)) return expr_error();

    return new ParenExpr(lparen_loc, lparen_loc, rparen_loc, expr, parentStmt);
}

Expr* Parser::parse_member_expr(Stmt* parentStmt) {

    SourceLocation sloc = loc();

    Name* name = 0;
    if (!parse_name(&name, true)) return 0;

    if (!expect_consume(TokenKind::Period)) return 0;

    Expr* expr = parse_cast_expr(parentStmt);

    return new MemberExpr(sloc, name, expr, 0, parentStmt);
}

Expr* Parser::parse_call_expr(
    Stmt* parentStmt,
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
        Expr* expr = parse_assignment_expr(parentStmt);
        args.push(expr);
        if (current.kind == TokenKind::Comma) {
            consume();
            continue;
        } else break;
    }

    if (!expect_consume(TokenKind::RParen)) return 0;
    if (expect_semi)
        if (!this->expect_semi()) return expr_error();

    return new CallExpr(sloc, name, 0, template_type, args, parentStmt);
}

} // namespace vc

