#include <vc/basic/sourcelocation.h>

namespace vc {

const SourceLocation SourceLocation::None = SourceLocation { u32(-1), u32(-1) };
const SourceRange SourceRange::None = SourceRange { SourceLocation::None, SourceLocation::None };

std::ostream& operator <<(std::ostream& out, const SourceLocation& sourceLocation) {
    out << "(Ln " 
        << sourceLocation.line 
        << ", Col " 
        << sourceLocation.column 
        << ")";
    return out;
}

std::ostream& operator <<(std::ostream& out, const SourceRange& sourceRange) {
    out << "{"
        << sourceRange.begin 
        << ", "
        << sourceRange.end
        << "}";
    return out;
}

} // namespace vc
