#ifndef VC_TOKEN_KIND_H_INCLUDE
#define VC_TOKEN_KIND_H_INCLUDE

#include <string>
#include <iostream>

namespace vc {

enum TokenKind {
    #define TOKEN_KIND(tokenKind) tokenKind,
    #include <vc/defs/tokenkinds.inl>
    #undef TOKEN_KIND
};

std::string toString(TokenKind tokenKind);
std::ostream& operator <<(std::ostream& out, const TokenKind& tokenKind);

}

#endif // VC_TOKEN_KIND_H_INCLUDE