#ifndef VC_SOURCE_LOCATION_H_INCLUDE
#define VC_SOURCE_LOCATION_H_INCLUDE

#include <vc/types.h>

namespace vc {

struct SourceLocation {
    u64 line;
    u64 column;
};

struct SourceRange {
    SourceLocation begin;
    SourceLocation end;
};

}

#endif // VC_SOURCE_LOCATION_H_INCLUDE