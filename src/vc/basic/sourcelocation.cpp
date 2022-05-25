#include <vc/basic/sourcelocation.h>

namespace vc {
    const SourceLocation SourceLocation::None = SourceLocation { u32(-1), u32(-1) };
    const SourceRange SourceRange::None = SourceRange { SourceLocation::None, SourceLocation::None };
}