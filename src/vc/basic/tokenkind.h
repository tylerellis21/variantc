#ifndef VC_TOKEN_KIND_H_INCLUDE
#define VC_TOKEN_KIND_H_INCLUDE

#include <string>

namespace vc {

enum TokenKind {
    #define TOKEN_KIND(tokenKind) tokenKind,
    #include <vc/defs/tokenkinds.inl>
    #undef TOKEN_KIND
};

std::string toString(TokenKind tokenKind);

}

#endif // VC_TOKEN_KIND_H_INCLUDE