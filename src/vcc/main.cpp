#include <string>
#include <vector>

#include <vc/compiler/lexer.h>
#include <vc/compiler/parser.h>

#include <vc/ast/astprinter.h>
#include <vc/ast/decl.h>
#include <vc/ast/declgroup.h>
#include <vc/ast/expr.h>
#include <vc/ast/stmt.h>
#include <vc/ast/type.h>
#include <vc/ast/name.h>

#include <vc/ir/ir_gen.h>
#include <vc/ir/ir_opcode.h>
#include <vc/ir/ir_optimizer.h>

#include <string>
#include <iostream>

using namespace vc;

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

        std::cout << token << std::endl;
    }

    // Reset the lexer for parsing,
    //remove if we aren't printing out the tokens.
    if (!lexer.open(input)) {
        return -1;
    }

    Parser parser(&lexer);
    if (!parser.open()) {
        return -1;
    }

    DeclGroup* moduleDeclGroup = new DeclGroup(0);
    ModuleDecl* moduleDecl = new ModuleDecl(0, SourceLocation::None, moduleDeclGroup);

    while (parser.valid()) {
        if (!parser.parseDecl(moduleDecl, moduleDeclGroup)) return -1;
    }

    printDecl(moduleDecl, 0);


    IRGen irGen;

    std::vector<ir_opcode> opcodes;

    std::string labelName = "hello";

    ir_opcode labelA(ir_label{labelName});
    ir_opcode nop(ir_nop{});
    ir_opcode allocate(ir_alloc{0, BuiltinKind::Uint32});

    opcodes.push_back(labelA);
    opcodes.push_back(nop);
    opcodes.push_back(allocate);

    for (int i = 0; i < opcodes.size(); i++) {
        ir_opcode opcode = opcodes[i];

        if (opcode.opcodeId != ir_opcode_id::Label) {
            std::cout << "    ";
        }

        std::cout << opcode;
    }

    return 0;
}
