#include <vc/basic/token.h>

namespace vc {

std::ostream& operator <<(std::ostream& out, const Token& token) {
    out << "'"
        << token.string.c_str()
        << "' "
        << token.kind
        << " "
        << token.loc;
    return out;
}

}