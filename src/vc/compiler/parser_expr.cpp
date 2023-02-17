#include <vc/compiler/parser.h>
#include <vc/basic/tokenprecedence.h>

namespace vc {

Expr* Parser::exprError() {
    consume();
    return 0;
}

Expr* Parser::parseExpr(Stmt* parentStmt) {
    Expr* lhs = parseAssignmentExpr(parentStmt);
    return parseRhsBinaryOp(parentStmt, lhs, (i32)TokenPrecedence::Comma);
}

Expr* Parser::parseAssignmentExpr(Stmt* parentStmt) {
    Expr* lhs = parseCastExpr(parentStmt);
    return parseRhsBinaryOp(parentStmt, lhs, (i32)TokenPrecedence::Assignment);
}

Expr* Parser::parseRhsBinaryOp(Stmt* parentStmt, Expr* lhs, i32 minPrecedence) {
    TokenPrecedence nextOperatorPrec = getTokenPrecedence(current.kind);

    while (1) {
        if ((i32)nextOperatorPrec < minPrecedence) break;
        Token opToken = current;
        consume();

        if (nextOperatorPrec == TokenPrecedence::Conditional) {
            lhs = parseTernaryExpr(parentStmt, lhs);
            break;
        }

        Expr* rhs = 0;
        if ((i32)nextOperatorPrec <= (i32)TokenPrecedence::Conditional)
            rhs = parseAssignmentExpr(parentStmt);
        else
            rhs = parseCastExpr(parentStmt);

        TokenPrecedence currentTokenPrec = nextOperatorPrec;
        nextOperatorPrec = getTokenPrecedence(current.kind);

        bool isRightAssoc = currentTokenPrec == TokenPrecedence::Conditional|| currentTokenPrec == TokenPrecedence::Assignment;

        if (currentTokenPrec < nextOperatorPrec || ((currentTokenPrec == nextOperatorPrec) && isRightAssoc)) {
            rhs = parseRhsBinaryOp(parentStmt, rhs, (i32)currentTokenPrec + !isRightAssoc);
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
        if (next.kind == TokenKind::LParen ||
            next.kind == TokenKind::At) {
            result = parseCallExpr(parentStmt, false);
        }
        else if (next.kind == TokenKind::Period) {
            result = parseMemberExpr(parentStmt);
        }
        else
            result = parseDeclRefExpr(parentStmt);
    } break;

    case TokenKind::Equal: {
        consume();
        result = parseAssignmentExpr(parentStmt);
    } break;

    case TokenKind::LParen: {
        result = parseParenExpr(parentStmt);
    } break;

    case TokenKind::Amp:
    case TokenKind::Star:
    case TokenKind::Exclaim:
    case TokenKind::Tilde:
    case TokenKind::Minus:
    case TokenKind::MinusMinus:
    case TokenKind::PlusPlus:
    case TokenKind::LSquare: {
        result = parsePostfixExpr(parentStmt, result, false);
    } break;

    case TokenKind::LBrace: {
        result = parseInitalizerExpr(parentStmt);
    } break;

    } // switch (parser->current.kind)

    switch (current.kind) {
    default: break;
    case TokenKind::PlusPlus:
    case TokenKind::MinusMinus:
    case TokenKind::LSquare: {
        result = parsePostfixExpr(parentStmt, result, true);
    } break;
    }

    return result;
}

Expr* Parser::parseTernaryExpr(Stmt* parentStmt, Expr* condition) {
    SourceLocation sloc = loc();
    Expr* lhs = parseCastExpr(parentStmt);
    if (!expectConsume(TokenKind::Colon)) return 0;
    Expr* rhs = parseCastExpr(parentStmt);
    return new TernaryExpr(
        parentStmt,
        sloc,
        condition,
        lhs,
        rhs
    );
}

Expr* Parser::parseInitalizerExpr(Stmt* parentStmt) {
    SourceLocation sloc = loc();

    std::vector<Expr*> values;
    SourceRange sourceRange;

    sourceRange.begin = loc();
    if (!expectConsume(TokenKind::LBrace)) return 0;

    while (valid()) {
        if (current.kind == TokenKind::RBrace) return 0;

        Expr* value = parseAssignmentExpr(parentStmt);

        values.push_back(value);

        if (current.kind == TokenKind::Comma) {
            consume();
            continue;
        } else break;
    }

    sourceRange.end = loc();
    if (!expectConsume(TokenKind::RBrace)) return 0;

    return new InitalizerExpr(
        parentStmt,
        sourceRange,
        values
    );
}

Expr* Parser::parseArraySubscriptExpr(Stmt* parentStmt, Expr* lhs) {
    SourceLocation sloc = loc();
    if (!expectConsume(TokenKind::LSquare)) return 0;
    Expr* rhs = parseCastExpr(parentStmt);
    if (!expectConsume(TokenKind::RSquare)) return 0;
    return new ArraySubscriptExpr(
        parentStmt,
        sloc,
        lhs,
        rhs
    );
}

Expr* Parser::parseUnaryExpr(Stmt* parentStmt, Expr* lhs, bool postfix) {
    Token op = current;
    consume();
    Expr* expr = lhs ? lhs : parseCastExpr(parentStmt);
    return new UnaryOpExpr(
        parentStmt,
        op.loc,
        postfix,
        expr,
        op
    );
}

Expr* Parser::parsePostfixExpr(Stmt* parentStmt, Expr* lhs, bool postfix) {
    switch(current.kind) {
    default: return 0;
    case TokenKind::Amp:
    case TokenKind::Exclaim:
    case TokenKind::Star:
    case TokenKind::Tilde:
    case TokenKind::Minus:
    case TokenKind::MinusMinus:
    case TokenKind::PlusPlus: return parseUnaryExpr(parentStmt, lhs, postfix);
    case TokenKind::LSquare: return parseArraySubscriptExpr(parentStmt, lhs);
    }
}

Expr* Parser::parseDeclRefExpr(Stmt* parentStmt) {
    SourceLocation sloc = loc();
    if (!expect(TokenKind::Identifier)) return exprError();

    Name name;
    if (!parseName(&name, true)) return exprError();

    return new DeclRefExpr(
        parentStmt,
        sloc,
        name
    );
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

Expr* Parser::parseLiteralExpr(Stmt* parentStmt) {
    switch (current.kind) {

    case TokenKind::BooleanLiteral: return parseBooleanLiteralExpr(parentStmt);
    case TokenKind::CharacterLiteral: return parseCharacterLiteralExpr(parentStmt);
    case TokenKind::StringLiteral: return parseStringLiteralExpr(parentStmt);
    case TokenKind::RealLiteral: return parseRealLiteralExpr(parentStmt);

    default: {
        printf("unhandled literal type\n");
        return exprError();
    }

    } // switch (current.kind)
}

Expr* Parser::parseBooleanLiteralExpr(Stmt* parentStmt) {
    if (!expect(TokenKind::BooleanLiteral)) return 0;

    SourceLocation sloc = loc();
    bool value;

    if (current.string.compare("true") == 0)
        value = true;
    else
        value = false;

    consume();

    return new BooleanLiteral(parentStmt, sloc, value);
}

Expr* Parser::parseCharacterLiteralExpr(Stmt* parentStmt) {

case TokenKind::CharacterLiteral: {

    u64 length = utf8_sequence_length(token.str.buffer[0]);
    rune value = utf8_decode_rune(token.str.buffer, length);

    result = new CharLiteral(token.loc, value, parentStmt);
} break;

}

Expr* Parser::parseStringLiteralExpr(Stmt* parentStmt) {

case TokenKind::StringLiteral: {
    result = new StringLiteral(token.loc, token.str, parentStmt);
} break;

}

Expr* Parser::parseIntegerLiteralExpr(Stmt* parentStmt) {

case TokenKind::IntegerLiteral: {
    // TODO: Figure out the proper integer type.
    //bool is_signed = token.str[0] == '-';
    i64 value = atoll((char*)token.str.buffer);
    result = new IntegerLiteral(token.loc, value, parentStmt);
} break;

}

Expr* Parser::parseRealLiteralExpr(Stmt* parentStmt) {

case TokenKind::RealLiteral: {
    r64 value = atof((char*)token.str.buffer);
    result = new RealLiteral(token.loc, value, parentStmt);
} break;

}

} // namespace vc

