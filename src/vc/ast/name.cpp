#include <vc/ast/name.h>

namespace vc {

std::ostream& operator <<(std::ostream& out, const Name& name) {
    for (int i = 0; i < name.identifiers.size(); i++) {
        out << name.identifiers[i].string;

        if (i + 1 < name.identifiers.size()) {
            out << "::";
        }
    }
    return out;
}

} // namespace vc