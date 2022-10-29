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
#include <vc/ast/name.h>

#include <vc/ir/ir_gen.h>
#include <vc/ir/ir_opcode.h>
#include <vc/ir/ir_optimizer.h>

using namespace vc;

#include <string>
#include <iostream>

int main(int argc, char** args) {

    if (argc <= 1) {
        printf("not enough arguments specified");
        return -1;
    }

    char* input = args[1];

    Lexer lexer;
    if (!lexer.open(input)) {
        return -1;
    }

    while (lexer.isMoreChars()) {
        char c = lexer.current;

        Token token;
        lexer.nextToken(&token);


        printf("%s {line: %ull, col: %ull} tokenKind: %i\n", token.string.c_str(), token.loc.line, token.loc.column, token.kind);
    }
    printf("\n");

    return 0;
}
