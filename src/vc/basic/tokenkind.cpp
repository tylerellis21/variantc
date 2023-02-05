#include <vc/basic/tokenkind.h>

namespace vc {

bool isBuiltinKind(TokenKind tokenKind) {
    switch (tokenKind) {
        #define BUILTIN_KIND(NAME, SYMBOL, SIZE) case TokenKind::##NAME:
        #include <vc/defs/builtin_kinds.inl>
            return true;
        #undef BUILTIN_KIND

        default: return false;
    }
}

bool isKeywordKind(TokenKind tokenKind) {
    switch (tokenKind) {
        #define TOKEN_KIND(NAME, SYMBOL) case TokenKind::##NAME:
        #include <vc/defs/lexer/token_keywords.inl>
            return true;
        #undef TOKEN_KIND

        default: return false;
    }
}

bool isOperatorKind(TokenKind tokenKind) {
    switch (tokenKind) {

        #define TOKEN_KIND(NAME, SYMBOL) case TokenKind::##NAME:
        #include <vc/defs/lexer/token_operators.inl>
            return true;
        #undef TOKEN_KIND

        default: return false;
    }
}

std::string toName(TokenKind tokenKind) {
    switch (tokenKind) {
        #define BUILTIN_KIND(NAME, SYMBOL, SIZE) case TokenKind::##NAME: return TOSTRING(NAME);
        #include <vc/defs/builtin_kinds.inl>
        #undef BUILTIN_KIND

        #define TOKEN_KIND(NAME, SYMBOL) case TokenKind::##NAME: return TOSTRING(NAME);
        #include <vc/defs/lexer/token_keywords.inl>
        #undef TOKEN_KIND

        #define TOKEN_KIND(NAME, SYMBOL) case TokenKind::##NAME: return TOSTRING(NAME);
        #include <vc/defs/lexer/token_literals.inl>
        #undef TOKEN_KIND

        #define TOKEN_KIND(NAME, SYMBOL) case TokenKind::##NAME: return TOSTRING(NAME);
        #include <vc/defs/lexer/token_operators.inl>
        #undef TOKEN_KIND

    default:
        return std::string("TOKEN KIND IS NOT SPECIFIED IN TOSTRING SWITCH");
    }
}

std::string toSymbol(TokenKind tokenKind) {
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
    out << toName(tokenKind);
    return out;
}

} // namespace vc