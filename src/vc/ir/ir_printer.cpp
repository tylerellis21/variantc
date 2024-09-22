#include <vc/ir/ir_printer.h>
#include <iostream>

namespace vc {

void IRPrinter::print(const ir_module& module) {
    std::cout << "." << module.name << " {" << std::endl;
    for (int i = 0; i < module.functions.size(); i++) {
        const auto& function = module.functions[i];
        indent(2);
        print(function);
    }
    std::cout << "}" << std::endl;
}

void IRPrinter::print(const ir_function& function) {

    if (function.args.size() > 0) {
        std::cout << function.name << "(";
        for (int i = 0; i < function.args.size(); i++) {
            const auto& arg = function.args[i];
            std::cout << "$" << arg.index << " " << builtinKindString(arg.type);
            if (i + 1 < function.args.size()) {
                std::cout << ",";
            }
        }
        std::cout << ") {" << std::endl;
    }

    for (int i = 0; i < function.opcodes.size(); i++) {
        //indent(2);
        print(function.opcodes[i]);
    }

    std::cout << "}" << std::endl;
}

void IRPrinter::print(const ir_opcode& opcode) {
    if (opcode.opcodeId != ir_opcode_id::Label) {
        std::cout << "  ";
    }
    std::cout << opcode;
}

void IRPrinter::indent(int indent) {
    for (int i = 0; i < indent; i++) {
        std::cout << " ";
    }
}

} // namespace vc