#include <vc/basic/token.h>

namespace vc {

std::ostream& operator <<(std::ostream& out, const Token& token) {
    out << "'"
        << token.string.c_str()
        << "' "
        << toString(token.kind)
        << " "
        << token.loc;
    return out;
}

}