#include <vc/basic/source_location.h>
#include <iostream>

namespace t {
namespace vc {

const SourceLocation SourceLocation::None = SourceLocation{u32(-1), u32(-1)};

void source_loc_print(SourceLocation location) {
    printf("<line:%i,%i>", location.line, location.column);
}

void source_range_print(SourceRange range) {
    printf("<line:%i,%i:%i,%i>",
           range.start.line,
           range.start.column,

           range.end.line,
           range.end.column);
}

} // namespace vc
} // namespace t
