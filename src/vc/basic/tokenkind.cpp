#include <vc/basic/tokenkind.h>

namespace vc {

std::string toString(TokenKind tokenKind) {
    switch (tokenKind) {
    default:
        return std::string("TOKEN KIND IS NOT SPECIFIED IN TOSTRING SWITCH");
    }
}

std::ostream& operator <<(std::ostream& out, const TokenKind& tokenKind) {
    out << toString(tokenKind);
    return out;
}

} // namespace vc