#include <vc/basic/tokenmap.h>

namespace vc {

const TokenMap tokenMap = {

    // Generate an entry for each of the builtin types.
    #define BUILTIN_KIND(NAME, SYMBOL, SIZE) { TOSTRING(SYMBOL), TokenKind::##NAME },
    #include <vc/defs/builtin_kinds.inl>
    #undef BUILTIN_KIND

    #define TOKEN_KIND(NAME, SYMBOL) { SYMBOL, TokenKind::##NAME },
    #include <vc/defs/lexer/token_keywords.inl>
    #undef TOKEN_KIND

    #define TOKEN_KIND(NAME, SYMBOL) { TOSTRING(SYMBOL), TokenKind::##NAME },
    #include <vc/defs/lexer/token_literals.inl>
    #undef TOKEN_KIND
    /*
    Don't include the token_operators.inl since they are lexed on a different branch than identifiers.
    #define TOKEN_KIND(NAME, SYMBOL) { SYMBOL, TokenKind::##NAME },
    #include <vc/defs/lexer/token_operators.inl>
    #undef TOKEN_KIND
    */

    { "false", TokenKind::BooleanLiteral },
    { "true", TokenKind::BooleanLiteral }
};

}
