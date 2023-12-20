#include <vc/parser.h>
#include <vc/val.h>
#include <vc/compiler.h>

#include <t/struct/stack.h>

#include <iostream>

namespace t {
namespace vc {

Name* resolve_full_name(Name* name, Decl* parent) {
    Name* full_name = new Name;

    // Build the full name starting from the root parent and work back

    Stack<Decl*> walk_list(256);

    while (parent) {
        walk_list.push(parent);
        if (parent->kind == DeclKind::NamespaceDecl) {
            parent = parent->parent;
        }
        else break;
    }

    while (walk_list.offset > 0) {
        Decl* decl = walk_list.pop();

        Name* dname = decl->name();
        if (dname) {
            for (utf8& id : dname->identifiers)
                full_name->identifiers.push(id);
        }
    }

    for (utf8& id : name->identifiers) full_name->identifiers.push(id);

    return full_name;
}

} // namespace vc
} // namespace t
