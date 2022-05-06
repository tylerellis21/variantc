#ifndef VC_DECL_GROUP_H_INCLUDE
#define VC_DECL_GROUP_H_INCLUDE
#include <vector>

namespace vc {

struct Decl;

struct DeclGroup {
    std::vector<Decl*> entries;
};

}

#endif // VC_DECL_GROUP_H_INCLUDE