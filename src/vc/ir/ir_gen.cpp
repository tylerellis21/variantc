#include <vc/ir/ir_gen.h>
#include <vc/ast/decl.h>

namespace vc {

void IRGen::generate(Decl* decl) {
    switch (decl->declKind) {
        default: 
        // something something unhandled declaration in ir generation
        break;
    }
}

}