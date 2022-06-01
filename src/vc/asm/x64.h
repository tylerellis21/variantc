#ifndef VC_X64_H_INCLUDE
#define VC_X64_H_INCLUDE

#include <vc/types.h>

namespace vc {
    
struct REX {
    union {
        struct {
            u8 fixed_bit_pattern : 4; // = 0b0100;

            // When 1, a 64-bit operand size is used. Otherwise, 
            // when 0, the default operand size is used (which is 32-bit for most but not all instructions)
            u8 W : 1;

            // This 1-bit value is an extension to the MODRM.reg field.
            u8 R : 1;

            // This 1-bit value is an extension to the SIB.index field.
            u8 X : 1;

            // This 1-bit value is an extension to the MODRM.rm field or the SIB.base field.
            u8 B : 1;
        };
        u8 byte;
    };
};

} // namespace vc

#endif // VC_X64_H_INCLUDE
