#include <vc/ir/ir_opcode.h>
#include <iostream>

namespace vc {

std::ostream& operator <<(std::ostream& out, const ir_opcode& opcode) {
    switch (opcode.opcodeId) {
        case ir_opcode_id::NOP:
            out << "NOP" << std::endl;
        break;

        case ir_opcode_id::Label:
            out << opcode.label.name << ":" << std::endl;
            break;

        case ir_opcode_id::CALL:

        break;

        case ir_opcode_id::RET:
        break;

        case ir_opcode_id::ALLOC:
            out << "ALLOC " << (opcode.alloc.alloc_type == ir_alloc_type::Stack ? "STACK " : "HEAP ");

            out << "$" << opcode.alloc.value.index
            << ", "
            << builtinKindString(opcode.alloc.value.type)
            << std::endl;
        break;

        case ir_opcode_id::LOAD:
        break;
/*
        LOAD
        STORE
        STORE_CONST
        CMP
        JO
        JNO
        JB
        JNB
        JZ
        JNZ
        JBE
        JNBE
        JS
        JNS
        JP
        JNP
        JL
        JNL
        JLE
        JNLE
        JG
        JGE
        JNG
        JNGE
        ADD
        SUB
        MUL
        DIV
        MOD
        INC
        DEC
        OR
        AND
        XOR
        NOT
        ROL
        ROR
        RCL
        RCR
        SHL
        SHR
        SAL
        SAR
*/
    }
    return out;
}

} // namespace vc
