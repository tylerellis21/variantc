#include <vc/ir/ir_opcode.h>
#include <iostream>

namespace vc {

std::ostream& operator <<(std::ostream& out, const ir_opcode& opcode) {
    switch (opcode.opcodeId) {
        case ir_opcode_id::NOP: out << "NOP" << std::endl; break;
        case ir_opcode_id::Label: out << opcode.label.name << ":" << std::endl; break;
    }
    return out;
}

} // namespace vc