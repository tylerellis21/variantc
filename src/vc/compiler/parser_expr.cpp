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

// TODO(@Tyler): Why is this seperated from parseExpr?
// I think there was a reason at one point

Expr* Parser::parseCastExpr(Stmt* parentStmt) {
    Expr* result = 0;

    switch (current.kind) {
    default: return 0;
    case TokenKind::BooleanLiteral:
    case TokenKind::CharacterLiteral:
    case TokenKind::IntegerLiteral:
    case TokenKind::Real32Literal:
    case TokenKind::Real64Literal:
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
        op.kind
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

Expr* Parser::parseParenExpr(Stmt* parentStmt) {
    SourceRange sourceRange = SourceRange::None;
    sourceRange.begin = loc();
    if (!expectConsume(TokenKind::LParen)) return exprError();

    Expr* expr = parseExpr(parentStmt);

    sourceRange.end = loc();
    if (!expectConsume(TokenKind::RParen)) return exprError();

    return new ParenExpr(parentStmt, sourceRange, expr);
}

Expr* Parser::parseMemberExpr(Stmt* parentStmt) {

    SourceLocation sloc = loc();

    Name name;
    if (!parseName(&name, true)) return 0;

    if (!expectConsume(TokenKind::Period)) return 0;

    Expr* expr = parseCastExpr(parentStmt);

    return new MemberExpr(parentStmt, sloc, name, expr);
}

Expr* Parser::parseCallExpr(
    Stmt* parentStmt,
    bool expectSemi) {

    SourceRange sourceRange;
    sourceRange.begin = loc();

    std::vector<Expr*> args;
/*
    if (next.kind == TokenKind::At) {
        if (!parseTemplateType(&templateType)) return exprError();
    }
    else if (name.identifiers.size() == 0)
*/
    Name name;
    if (!parseName(&name, true)) return 0;

    if (!expectConsume(TokenKind::LParen)) return 0;

    while (valid()) {
        if (current.kind == TokenKind::RParen) break;

        Expr* expr = parseAssignmentExpr(parentStmt);

        args.push_back(expr);

        if (current.kind == TokenKind::Comma) {
            consume();
            continue;
        } else break;
    }
    sourceRange.end = loc();
    if (!expectConsume(TokenKind::RParen)) return 0;

    if (expectSemi && !this->expectSemi())
        return exprError();

    return new CallExpr(parentStmt, sourceRange, name, args);
}

Expr* Parser::parseLiteralExpr(Stmt* parentStmt) {
    switch (current.kind) {

    case TokenKind::BooleanLiteral: return parseBooleanLiteralExpr(parentStmt);
    case TokenKind::CharacterLiteral: return parseCharacterLiteralExpr(parentStmt);
    case TokenKind::StringLiteral: return parseStringLiteralExpr(parentStmt);
    case TokenKind::IntegerLiteral: return parseIntegerLiteralExpr(parentStmt);

    case TokenKind::Real32Literal:
    case TokenKind::Real64Literal: return parseRealLiteralExpr(parentStmt);


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

    return new BooleanLiteralExpr(parentStmt, sloc, value);
}

Expr* Parser::parseCharacterLiteralExpr(Stmt* parentStmt) {

    //u64 length = utf8_sequence_length(token.str.buffer[0]);
    //rune value = utf8_decode_rune(token.str.buffer, length);
    // TODO(@Tyler): Implement unicode character support

    // TODO(@Tyler): I was thinking... since we are using utf8, do we really need character literals?
    //since one character doesn't really equal to one byte.
    //so what if we just used string literals instead?
    // a 1 character string literal is literally the same thing right?!?

    rune value = *current.string.begin();
    consume();

    return new CharLiteralExpr(parentStmt, current.loc, value);
}

Expr* Parser::parseStringLiteralExpr(Stmt* parentStmt) {
    SourceLocation sloc = loc();
    std::string value = current.string;
    consume();
    // TODO(@Tyler): Implement unicode character support
    return new StringLiteralExpr(parentStmt, sloc, value);
}

Expr* Parser::parseIntegerLiteralExpr(Stmt* parentStmt) {
    SourceLocation sloc = loc();
    // TODO: Figure out the proper integer type.
    //bool is_signed = token.str[0] == '-';
    i64 value = atoll((char*)current.string.c_str());
    consume();
    IntegerLiteralExpr* result;
    
    if (value < 0) {
        result = new IntegerLiteralExpr(parentStmt, sloc, BuiltinKind::Uint64);
        result->u64_value = (u64)value;
        return result;
    }

    result = new IntegerLiteralExpr(parentStmt, sloc, BuiltinKind::Int64);
    result->i64_value = value;
    return result;
}

Expr* Parser::parseRealLiteralExpr(Stmt* parentStmt) {
    TokenKind tokenKind = current.kind;
    SourceLocation sloc = loc();
    r64 value = atof((char*)current.string.c_str());
    consume();

    BuiltinKind builtinKind;
    if (current.kind == TokenKind::Real32Literal) {
        return new RealLiteralExpr(parentStmt, sloc, (r32)value);
    }
    else if (current.kind == TokenKind::Real64Literal) {
        return new RealLiteralExpr(parentStmt, sloc, value);
    }
    return 0;
}

} // namespace vc

