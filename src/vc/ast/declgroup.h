#ifndef VC_DECL_GROUP_H_INCLUDE
#define VC_DECL_GROUP_H_INCLUDE

#include <vector>

namespace vc {

struct Decl;

struct DeclGroup {
    DeclGroup* parent;

    std::vector<Decl*> entries;

    DeclGroup(DeclGroup* parent) :
        parent(parent),
        entries(std::vector<Decl*>())
    { }

    inline void add(Decl* decl) {
        entries.push_back(decl);
    }
};

} // namespace vc

#endif // VC_DECL_GROUP_H_INCLUDE