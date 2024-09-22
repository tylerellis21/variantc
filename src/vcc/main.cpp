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
#include <vc/ir/ir_opcodelist.h>
#include <vc/ir/ir_optimizer.h>
#include <vc/ir/ir_printer.h>

#include <string>
#include <iostream>

using namespace vc;

int main(int argc, char **args) {

    if (argc <= 1) {
        printf("not enough arguments specified");
        return -1;
    }

    char *input = args[1];

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
    // remove if we aren't printing out the tokens.
    if (!lexer.open(input)) {
        return -1;
    }

    Parser parser(&lexer);
    if (!parser.open()) {
        return -1;
    }

    DeclGroup *moduleDeclGroup = new DeclGroup(0);
    ModuleDecl *moduleDecl = new ModuleDecl(0, SourceLocation::None, moduleDeclGroup);

    while (parser.valid()) {
        if (!parser.parseDecl(moduleDecl, moduleDeclGroup))
            return -1;
    }

    printDecl(moduleDecl, 0);

    IRGen irGen;

    std::cout << "ir_opcode size: " << IR_OPCODE_SIZE << std::endl;


    ir_module module = irGen.generateModule(moduleDecl);
    // TODO: Find the module name?!
    module.name = "test";

    ir_function func;
    func.name = "add";

    func.args.push_back(ir_ssa_value{0, BuiltinKind::Int32});
    func.args.push_back(ir_ssa_value{1, BuiltinKind::Int32});


    std::string labelName = "hello";

    ir_opcode labelA(ir_label{labelName});
    ir_opcode nop(ir_nop{});
    ir_opcode allocate(ir_alloc(ir_ssa_value(0, BuiltinKind::Uint32), ir_alloc_type::Heap));

    func.opcodes.push_back(labelA);
    func.opcodes.push_back(nop);
    func.opcodes.push_back(allocate);

    module.functions.push_back(func);

    IRPrinter printer;
    printer.print(module);

    return 0;
}
