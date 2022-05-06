#ifndef IR_OPCODE_H_INCLUDE
#define IR_OPCODE_H_INCLUDE

namespace vc {

enum IROpcodeType {
    NOP = 0,
};

struct IROpcode {
    union {
        
    };
};

struct ir_label {

};

struct ir_nop { };

struct ir_cmp { 

};

struct ir_jmp { 

};

struct ir_je { 

};

struct ir_jne { 

};

struct ir_jg { 

};

struct ir_jge { 

};

struct ir_jl {

};

struct ir_jle { 
};

struct ir_mov {
};

struct ir_push {
};

struct ir_pop {

};

struct ir_load {
};

struct ir_store {
};


/*

mov rax, rbx

mov i32 a, b

load i32 $0
store i32 $1

*/


}

#endif // IR_OPCODE_H_INCLUDE