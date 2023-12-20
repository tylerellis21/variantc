#ifndef VM_H_INCLUDE
#define VM_H_INCLUDE

#include <t/core/string.h>
#include <t/struct/stack.h>

#include <vc/basic/convert.h>
#include <vc/opcode.h>

namespace t {
namespace vc {

#define VM_STACK_SIZE 512
#define VM_LOCAL_SIZE 65536

struct Bytecode {
   u8* data;
   u64 length;
};

struct Method {
    u16 arg_count;
    u16 local_count;

    utf8 name;

    Bytecode code;
};

struct VM {

    // Frame pointer
    u64 fp;
    // Stack pointer
    u64 sp;

    // Each stack element is 64 bits.
    // The stack pointer is the "offset" in the stack struct.
    //Stack<i64> stack;
    i64* stack;

    inline i64 stack_top() {
        return stack[sp-1];
    }

    inline i64 stack_pop() {
        return stack[--sp];
    }

    inline void stack_push(i64 value) {
        stack[sp++] = value;
    }

    // Locals are saved bitwise
    u8* locals;

    Method* methods[256];

    inline VM() :
        fp(0),
        sp(0),
        stack(new i64[VM_STACK_SIZE]),
        locals(new u8[VM_LOCAL_SIZE])
    { }

    void invoke(u8* code, u64 code_length);

    inline void invoke(Bytecode bc) {
        invoke(bc.data, bc.length);
    }

    inline void invoke(Method method) {
        invoke(method.code);
    }
};

} // namespace vc
} // namespace t

#endif // VM_H_INCLUDE
