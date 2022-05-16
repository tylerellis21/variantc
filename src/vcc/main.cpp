#include <string>
#include <vector>

#include <vc/compiler/lexer.h>
#include <vc/basic/filebuffer.h>

// Let's work backwards. Let's build the ast structure then attempt to build the ir code generation before we 
// build out the entire lexer/parser/compiler

#include <vc/ast/decl.h>
#include <vc/ast/declgroup.h>
#include <vc/ast/expr.h>
#include <vc/ast/stmt.h>
#include <vc/ast/type.h>

#include <vc/ir/ir_gen.h>
#include <vc/ir/ir_opcode.h>
#include <vc/ir/ir_optimizer.h>

using namespace vc;

int main(int argc, char** args) {

    char* input = args[1];

    FileBuffer fb;
    if (fb.load(input) == false) {
        return -1;
    }

    SourceLocation none {u64(-1), u64(-1)};
    DeclGroup* moduleGroup = new DeclGroup(0);

    ModuleDecl* decl = new ModuleDecl {
        0,
        none,
        moduleGroup
    };

    
    return 0;
}