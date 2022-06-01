#ifndef VC_X86_H_INCLUDE
#define VC_X86_H_INCLUDE

#include <vc/types.h>

// Instructions are stored in memory in little-endian order. 

namespace vc {

// Instruction Prefixes

// mode-register-memory (ModRM)
struct ModRM {
    union {
        struct {
            // When this field is b11, then register-direct addressing mode is used; 
            // otherwise register-indirect addressing mode is used.
            u8 mod : 2;

            // This field can have one of two values:
            // A 3-bit opcode extension, which is used by some instructions but has no further meaning other than distinguishing the instruction from other instructions.
            // A 3-bit register reference, which can be used as the source or the destination of an instruction (depending on the instruction). (This specifies the G operand)
            u8 reg : 3;

            // Specifies a direct or indirect register operand, optionally with a displacement
            u8 rm : 3;
        };
        u8 byte;
    };
};

// scale-index-base (SIB) byte
struct SIB {
    union {
        struct {
            u8 scale : 2;
            u8 index : 3;
            u8 base : 3;
        };
        u8 byte;
    };
};



} // namespace vc

#endif // VC_X86_H_INCLUDE 