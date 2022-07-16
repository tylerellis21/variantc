#ifndef VC_SOURCE_LOCATION_H_INCLUDE
#define VC_SOURCE_LOCATION_H_INCLUDE

#include <iostream>

#include <vc/types.h>

namespace vc {

struct SourceLocation {
    u64 line;
    u64 column;
    
    const static SourceLocation None;
};

struct SourceRange {
    SourceLocation begin;
    SourceLocation end;

    const static SourceRange None;
};

std::ostream& operator <<(std::ostream& out, const SourceLocation& sourceLocation);
std::ostream& operator <<(std::ostream& out, const SourceRange& sourceRange);

} // namespace vc

#endif // VC_SOURCE_LOCATION_H_INCLUDE