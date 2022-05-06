#ifndef VC_SOURCE_LOCATION_H_INCLUDE
#define VC_SOURCE_LOCATION_H_INCLUDE

namespace vc {

struct SourceLocation {
    int line;
    int column;
};

struct SourceRange {
    SourceLocation begin;
    SourceLocation end;
};

}

#endif // VC_SOURCE_LOCATION_H_INCLUDE