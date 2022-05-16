#ifndef VC_DECL_GROUP_H_INCLUDE
#define VC_DECL_GROUP_H_INCLUDE

#include <vector>

namespace vc {

struct Decl;

struct DeclGroup {
    Decl* parent;
    std::vector<Decl*> entries;

    DeclGroup(Decl* parent) :
        parent(parent),
        entries(std::vector<Decl*>())
    { }
};

} // namespace vc

#endif // VC_DECL_GROUP_H_INCLUDE