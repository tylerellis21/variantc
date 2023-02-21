#include <vc/compiler/parser.h>

namespace vc {

bool Parser::parseBuiltinType(Type** type) {
    BuiltinKind builtinKind = builtinKindFromTokenKind(current.kind);
    SourceLocation keywordLoc = loc();
    *type = new BuiltinType(keywordLoc, builtinKind);
    consume();
    return true;
}

bool Parser::parsePointerType(Type** type) {
    *type = new PointerType(loc(), *type);
    consume();
    return true;
}

bool Parser::parseDeclRefType(Type** type) {
    SourceLocation sloc = loc();
    Name name;
    if (!parseName(&name, true)) return false;
    *type = new DeclRefType(sloc, name);
    // Don't consume since the parse_name did that for us
    return true;
}

bool Parser::parseArrayType(Type** type) {
    if (!expectConsume(TokenKind::LSquare)) return false;
    // NOTE(Tyler): Does this expression need a parent?
    // How does this effect validation?
    Expr* length = parseExpr(0);
    if (length->exprKind != ExprKind::IntegerLiteralExpr) {
        //report_error(lexer->fb, loc(), "expected integer literal\n");
        std::cout << "expected integer literal at: " << prev << std::endl;
        return false;
    }
    *type = new ArrayType(loc(), *type, static_cast<IntegerLiteralExpr*>(length)->u64_value);
    if (!expectConsume(TokenKind::RSquare)) return false;
    return true;
}

bool Parser::parseVarargType(Type** type) {
    //*type = new VarArgType(loc(), *type);
    *type = nullptr;
    consume();
    return true;
}

bool Parser::parseType(Type** type, bool first_call) {

    // We break out of the switch in the cases below
    // so that then end of the function can handle recursion if needed
    // we use this for types such as
    // i32**
    // where the first call would parse the 'i32'
    // second call the first '*'
    // and the third would be the last '*'

    switch (current.kind) {

    // We can only parse identifiers as a type on the first call
    // otherwise we risk consuming tokens that aren't part of the type

    case TokenKind::Identifier: {
        if (!parseDeclRefType(type)) return false;
        // Return true since we have hit the end of the type
        // i32** i = 0;
        //       ^
    } break;

    case TokenKind::Star: {
        if (!parsePointerType(type)) return false;
    } break;

    case TokenKind::LSquare: {
        if (!parseArrayType(type)) return false;
    } break;

    case TokenKind::Ellipsis: {
        if (!parseVarargType(type)) return false;
    } break;
/*
    case TokenKind::Less: {
        if (!parse_template_type(type)) return false;
    } break;
*/

    // Dispatch all basic kinds to the parse basic type method.
    {
        #define BUILTIN_KIND(NAME, SYMBOL, SIZE) case TokenKind::##NAME:
        #include <vc/defs/builtin_kinds.inl>
        #undef BUILTIN_KIND

        if (!parseBuiltinType(type)) return false;
        break;
    }

    default: {
        //report_error(lexer->fb, current.loc, "unexpected token in type: %s\n", token_symbol_or_string(current.kind).buffer);
        std::cout << "unexpected token in type: " << current << std::endl;
        return false;
    }

    } // switch (current.kind)

    if (isTypeTokenKind(current.kind)) {
        return parseType(type, false);
    }

    return true;
}

} // namespace vc
