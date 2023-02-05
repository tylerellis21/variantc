#ifndef VC_TOKEN_KIND_H_INCLUDE
#define VC_TOKEN_KIND_H_INCLUDE

#include <string>
#include <iostream>

#include <vc/macros.h>

namespace vc {

enum class TokenKind {
    None = 0,

    #define BUILTIN_KIND(NAME, SYMBOL, SIZE) NAME,
    #include <vc/defs/builtin_kinds.inl>
    #undef BUILTIN_KIND

    #define TOKEN_KIND(NAME, SYMBOL) NAME,
    #include <vc/defs/lexer/token_keywords.inl>
    #undef TOKEN_KIND

    #define TOKEN_KIND(NAME, SYMBOL) NAME,
    #include <vc/defs/lexer/token_literals.inl>
    #undef TOKEN_KIND

    #define TOKEN_KIND(NAME, SYMBOL) NAME,
    #include <vc/defs/lexer/token_operators.inl>
    #undef TOKEN_KIND
};

bool isBuiltinKind(TokenKind tokenKind);
bool isKeywordKind(TokenKind tokenKind);
bool isOperatorKind(TokenKind tokenKind);

std::string toName(TokenKind tokenKind);
std::string toSymbol(TokenKind tokenKind);

std::ostream& operator <<(std::ostream& out, const TokenKind& tokenKind);

}

#endif // VC_TOKEN_KIND_H_INCLUDE