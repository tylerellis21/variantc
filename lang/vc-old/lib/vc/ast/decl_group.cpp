#include <vc/ast/decl_group.h>
#include <vc/ast/decl.h>
namespace t {
namespace vc {

bool DeclGroup::contains(Decl* decl)  {
    for (Decl* item : decls) {
        if (decl_compare(item, decl)) return true;
    }
    return false;
}

} // namespace vc
} // namespace t
