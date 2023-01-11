#include <vc/basic/tokenkind.h>

namespace vc {

std::string toString(TokenKind tokenKind) {
    switch (tokenKind) {
        #define BUILTIN_KIND(NAME, SYMBOL, SIZE) case TokenKind::##NAME: return TOSTRING(SYMBOL);
        #include <vc/defs/builtin_kinds.inl>
        #undef BUILTIN_KIND

        #define TOKEN_KIND(NAME, SYMBOL) case TokenKind::##NAME: return TOSTRING(SYMBOL);
        #include <vc/defs/lexer/token_keywords.inl>
        #undef TOKEN_KIND

        #define TOKEN_KIND(NAME, SYMBOL) case TokenKind::##NAME: return TOSTRING(SYMBOL);
        #include <vc/defs/lexer/token_literals.inl>
        #undef TOKEN_KIND

        #define TOKEN_KIND(NAME, SYMBOL) case TokenKind::##NAME: return SYMBOL;
        #include <vc/defs/lexer/token_operators.inl>
        #undef TOKEN_KIND

    default:
        return std::string("TOKEN KIND IS NOT SPECIFIED IN TOSTRING SWITCH");
    }
}

std::ostream& operator <<(std::ostream& out, const TokenKind& tokenKind) {
    std::string symbolString = toString(tokenKind);
    if (symbolString.length())
        out << symbolString;
    return out;
}

} // namespace vc