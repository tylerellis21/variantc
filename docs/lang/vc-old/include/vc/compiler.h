#ifndef COMPILER_H_INCLUDE
#define COMPILER_H_INCLUDE

#include <t/core/string.h>
#include <t/struct/list.h>

#include <vc/ast/decl.h>
#include <vc/parser.h>
#include <vc/val.h>

namespace t {
namespace vc {

struct InputFile {
    utf8 file_name;
    utf8 file_path;
};

struct Module {

    utf8 name;
    utf8 file_name;
    utf8 file_path;

    Decl* ast;

    List<ImportDecl*> imports;

    // A list of 'typed' template declarations
    // AKA the result of the template expantions
    // TODO(Tyler): Perhaps move this into the parser?
    List<Decl*> template_records;

    // The file buffer containing the source code text.
    FileBuffer* fb;

    // Generated IR
    inline Module() :
        imports(List<ImportDecl*>(1)),
        template_records(List<Decl*>(1))
    { }
};

struct CompilerFlags {
    bool print_ast = true;
    bool print_ir = true;

    bool is_64bit = true;

    RBTree<Name> definitions;
};

struct Compiler {

    utf8 out_dir;

    // Directories used for searching when a module has an import
    List<utf8> search_directories;

    // list of the inital input files, not including the source code generated imports.
    List<InputFile> input_files;

    // list of all the modules loaded by the compiler.
    List<Module*> modules;

    CompilerFlags flags;

    inline Compiler() :
        search_directories(List<utf8>(1)),
        input_files(List<InputFile>(1)),
        modules(List<Module*>(1)) {
        search_directories.push("./");
    }

    bool compile();

    bool compile_module(Module* module);

    Module* add_file(utf8 file_name, utf8 file_path);
};

} // namespace vc
} // namespace t

#endif // COMPILER_H_INCLUDE
