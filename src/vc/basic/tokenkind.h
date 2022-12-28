#ifndef VC_TOKEN_KIND_H_INCLUDE
#define VC_TOKEN_KIND_H_INCLUDE

#include <string>
#include <iostream>

#include <vc/macros.h>

namespace vc {

enum class TokenKind {

    #define TOKEN_KIND(TOKEN_NAME, TOKEN_SYMBOL) TOKEN_NAME,
    #undef TOKEN_KIND

    #define BUILTIN_KIND(TOKEN_NAME, TOKEN_SYMBOL, SIZE_IN_BYTES) TOKEN_NAME,
    #undef BUILTIN_KIND
};

std::string toString(TokenKind tokenKind);
std::ostream& operator <<(std::ostream& out, const TokenKind& tokenKind);

}

#endif // VC_TOKEN_KIND_H_INCLUDE