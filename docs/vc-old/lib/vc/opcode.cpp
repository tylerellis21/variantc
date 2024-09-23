#include <vc/opcode.h>

namespace t {
namespace vc {

utf8 opcode_type_strings[] = {
    #define OPCODE_TYPE(TYPE_NAME, TYPE_STRING) TYPE_STRING,
    OPCODE_TYPES
    #undef OPCODE_TYPE
};

utf8 opcode_type_str(OpcodeType type) {
    return opcode_type_strings[i64(type)];
}

void opcode_print_type(OpcodeType type) {
    utf8 type_string = opcode_type_str(type);
    printf("%s", type_string.buffer);
}

utf8 opcode_memonic_strings[] = {
    #define OPCODE(MEMONIC) #MEMONIC,
    OPCODES
    #undef OPCODE
};

utf8 opcode_memonic_str(OpcodeId id) {
    return opcode_memonic_strings[i64(id)];
}

void opcode_print_args(OpcodeType type, Args args) {
    switch (type) {
    case OpcodeType::type_null:
        break;
    case OpcodeType::type_u8: printf("%i", args._u8); break;
    case OpcodeType::type_u16: printf("%i", args._u16); break;
    case OpcodeType::type_u32: printf("%i", args._u32); break;
    case OpcodeType::type_u64: printf("%llu", args._u64); break;
    case OpcodeType::type_i8: printf("%i", args._i8); break;
    case OpcodeType::type_i16: printf("%i", args._i16); break;
    case OpcodeType::type_i32: printf("%i", args._i32); break;
    case OpcodeType::type_i64: printf("%lli", args._i64); break;
    case OpcodeType::type_r32: printf("%f", args._r32); break;
    case OpcodeType::type_r64: printf("%f", args._r64); break;
    } // switch (type)
}

void opcode_print(Opcode opcode) {
    utf8 memonic_str = opcode_memonic_str(opcode.id);

    printf("%s ", memonic_str.buffer);

    switch (opcode.id) {

    case NOP: break;
    case HLT: break;

    case LOAD:
        opcode_print_type(opcode.load.type);
        printf(" $%llu", (u64)opcode.load.address);
       break;

    case STORE:
        opcode_print_type(opcode.store.type);
        printf(" $%llu", (u64)opcode.store.address);
        break;

    case LLOAD:
        opcode_print_type(opcode.lload.type);
        printf(" %%%llu", (u64)opcode.lload.address);
        break;

    case LSTORE:
        opcode_print_type(opcode.lstore.type);
        printf(" %%%llu", (u64)opcode.lstore.address);
        break;

    case REFLOAD: break;

    case REFSTORE: break;

    case CMP:
        opcode_print_type(opcode.cmp.type);
        break;
        
    case PUSH8:
        printf("%i", opcode.push8.value);
        break;

    case PUSH16:
        printf("%i", opcode.push16.value);
        break;

    case PUSH32:
        printf("%i", opcode.push32.value);
        break;

    case PUSH64:
        printf("%llu", opcode.push64.value);
        break;

    case POP: break;
    case POP2: break;
    case DUP: break;
    case DUP2: break;

    case CALL:
        printf("%i %i", 
            opcode.call.index,
            opcode.call.arg_count);
    break;

    case RET: break;

    case JMP:
        printf("%i", opcode.jmp.address); 
        break;
        
    case LJMP: 
        printf("%i", opcode.ljmp.address); 
        break;

    case JE: 
        printf("%i", opcode.je.address); 
        break;

    case JNE: 
        printf("%i", opcode.jne.address); 
        break;

    case JL: 
        printf("%i", opcode.jl.address); 
        break;

    case JLE: 
        printf("%i", opcode.jle.address); 
        break;

    case JG: 
        printf("%i", opcode.jg.address); 
        break;

    case JGE: 
        printf("%i", opcode.jge.address); 
        break;
        
    case ADD:
        opcode_print_type(opcode.add.type);
        break;

    case SUB: 
        opcode_print_type(opcode.sub.type);
        break;

    case MUL: 
        opcode_print_type(opcode.mul.type);
        break;

    case DIV: 
        opcode_print_type(opcode.div.type);
        break;
        
    case MOD: 
        opcode_print_type(opcode.mod.type);
        break;

    case BSL: 
        opcode_print_type(opcode.bsl.type);
        break;

    case BSR: 
        opcode_print_type(opcode.bsr.type);
        break;

    case NOT: 
        opcode_print_type(opcode._not.type);
        break;
    case AND: 
        opcode_print_type(opcode._and.type);
        break;

    case OR: 
        opcode_print_type(opcode._or.type);
        break;

    case XOR: 
        opcode_print_type(opcode._xor.type);
        break;

    case INC: 
        opcode_print_type(opcode.inc.type);
        break;

    case DEC: 
        opcode_print_type(opcode.dec.type);
        break;

    case PRINT_STACK_TOP: 
        break;

    case SLEEP: break;
    
    } // case opcode.id

    // The final new line for every opcode
    printf("\n");
}

} // namespace vc
} // namespace t
