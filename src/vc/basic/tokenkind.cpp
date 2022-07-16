#include <vc/basic/tokenkind.h>

namespace vc {
    
std::string toString(TokenKind tokenKind) {
    switch (tokenKind) {

    #define TOKEN_KIND(tokenKind) case TokenKind::tokenKind: return std::string(#tokenKind);
    #include <vc/defs/tokenkinds.inl>
    #undef TOKEN_KIND
    default: return std::string("TOKEN KIND IS NOT SPECIFIED IN TOSTRING SWITCH");
    }
}

std::ostream& operator <<(std::ostream& out, const TokenKind& tokenKind) {
    out << toString(tokenKind);
    return out;
}

}