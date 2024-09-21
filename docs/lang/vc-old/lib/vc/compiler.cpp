#include <vc/compiler.h>
#include <vc/ast/printer.h>
#include <vc/opgen.h>

namespace t {
namespace vc {

bool Compiler::compile() {
    // Generate a new module for each input file
    // We do it this way since the number of modules might not match the number of input files since
    // modules will need to import other modules

    // TODO(Tyler): Refactor this into something cleaner
    for (InputFile file : input_files) {
        Module* module = add_file(file.file_name, file.file_path);
        if (!compile_module(module)) return false;
    }

    return true;
}

bool Compiler::compile_module(Module* module) {

    module->fb = new FileBuffer(module->file_path);
    if (!module->fb->read()) {
        return false;
    }

    Lexer lexer(module->fb);
    if (!lexer.open()) {
        return false;
    }

    Parser parser(&lexer, module);
    if (!parser.open()) {
        return false;
    }

    if (!parser.parse(&module->ast)) {
        return false;
    }

    AstPrinter printer(stdout);
    printer.print(module->ast);

    Val val(module->fb, module, &flags);
    if (!val.validate(module->ast)) return false;

    OPGen opgen;
    opgen.generate(module->ast);

    for (OPGenFunction* result : opgen.functions) {
        name_print(result->name);
        printf(":\n");

        //printf(": (args=%u)", 

        for (Opcode& opcode : result->opcodes) {
            opcode_print(opcode);
        }
        printf("\n\n");
    }

    return true;
}

Module* Compiler::add_file(utf8 file_name, utf8 file_path) {
    Module* new_mod = new Module;
    new_mod->name = path::no_ext(file_name);
    new_mod->file_name = file_name;
    new_mod->file_path = file_path;
    modules.push(new_mod);
    return new_mod;
}

} // namespace vc
} // namespace t
