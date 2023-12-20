#include <vc/vm.h>
#include <t/core/sys/time.h>

namespace t {
namespace vc {

inline u8 read_u8(u8* src) {
    return *src;
}

inline u8 read_u8(u8* src, u64& offset) {
    u8 result = read_u8(src + offset);
    offset++;
    return result;
}

inline u16 read_u16(u8* src) {
    return read_u8(src) | (read_u8(src + 1) << 8);
}

inline u16 read_u16(u8* src, u64& offset) {
    u16 result = read_u16(src + offset);
    offset += 2;
    return result;
}
inline u32 read_u32(u8* src) {
    return (read_u8(src))
         | (read_u8(src + 1) << 8)
         | (read_u8(src + 2) << 16)
         | (read_u8(src + 3) << 24);
}

inline u32 read_u32(u8* src, u64& offset) {
    u32 result = read_u32(src + offset);
    offset += 4;
    return result;
}

inline u64 read_u64(u8* src) {
    return ((u64)read_u8(src))
         | ((u64)read_u8(src + 1) << 8)
         | ((u64)read_u8(src + 2) << 16)
         | ((u64)read_u8(src + 3) << 24)
         | ((u64)read_u8(src + 4) << 32)
         | ((u64)read_u8(src + 5) << 40)
         | ((u64)read_u8(src + 6) << 48)
         | ((u64)read_u8(src + 7) << 56);
}

inline u64 read_u64(u8* src, u64& offset) {
    u64 result = read_u64(src + offset);
    offset += 8;
    return result;
}

inline void write_u8(u8* dest, u8 value) {
   *dest = value;
}

inline void write_u16(u8* dest, u16 value) {
   *dest = (u8)value;
   *(dest + 1) = u8(value >> 8);
}

inline void write_u32(u8* dest, u32 value) {
   *dest = (u8)value;
   *(dest + 1) = u8(value >> 8);
   *(dest + 2) = u8(value >> 16);
   *(dest + 3) = u8(value >> 24);
}

inline void write_u64(u8* dest, u64 value) {
   *dest = (u8)value;
   *(dest + 1) = u8(value >> 8);
   *(dest + 2) = u8(value >> 16);
   *(dest + 3) = u8(value >> 24);
   *(dest + 4) = u8(value >> 32);
   *(dest + 5) = u8(value >> 40);
   *(dest + 6) = u8(value >> 48);
   *(dest + 7) = u8(value >> 56);
}

void VM::invoke(u8* code, u64 code_length) {

    bool run = true;

    u64 ip = 0;

    while (ip < code_length && run) {
        // Read in the opcode
        u8 opcode_id = read_u8(code, ip);

        switch (opcode_id) {

        case NOP: break;

        case PRINT_STACK_TOP: {
            printf("%f\n", to_r32((i32)stack_top()));
        } break;

        case SLEEP:
            t::sleep(stack_pop());
            break;

        case HLT:
            run = false;
            break;

        // Loads a local value onto the stack based on the given type.
        case LOAD: {
            u8 type = read_u8(code, ip);
            u16 address = read_u16(code, ip);

            switch (type) {
            case type_null: break;

            case type_u8:
            case type_i8: {
                u8* src = locals + address;
                u8 value = read_u8(src);
                stack_push(value);
            } break;

            case type_u16:
            case type_i16: {
                u8* src = locals + address;
                u16 value = read_u16(src);
                stack_push(value);
            } break;

            case type_r32:
            case type_u32:
            case type_i32: {
                u8* src = locals + address;
                u32 value = read_u32(src);
                stack_push(value);
            } break;

            case type_r64:
            case type_u64:
            case type_i64: {
                u8* src = locals + address;
                u64 value = read_u64(src);
                stack_push(value);
            } break;

            } // switch (type)
        } break;

        case STORE: {
            u8 type = read_u8(code, ip);
            u16 address = read_u16(code, ip);

            switch (type) {
            case type_null: break;

            case type_u8:
            case type_i8: {
                u8* dest = locals + address;
                u8 value = (u8)stack_pop();
                write_u8(dest, value);
            } break;

            case type_u16:
            case type_i16: {
                u8* dest = locals + address;
                u16 value = (u16)stack_pop();
                write_u16(dest, value);
            } break;

            case type_r32:
            case type_u32:
            case type_i32: {
                u8* dest = locals + address;
                u32 value = (u32)stack_pop();
                write_u32(dest, value);
            } break;

            case type_r64:
            case type_u64:
            case type_i64: {
                u8* dest = locals + address;
                u64 value = (u64)stack_pop();
                write_u64(dest, value);
            } break;


            } // switch (type)
        } break;
/*
        case FP_INC: {
            u16 value = read_u16(code, ip);
            fp += value;
        } break;

        case FP_DEC: {
            u16 value = read_u16(code, ip);
            fp -= value;
        } break;
*/
        // Loads a local value onto the stack based on the given type.
        case LLOAD: {
            u16 offset = read_u16(code, ip);
            i64 value = stack[fp - offset];
            printf("loaded value: %lli\n", value);
            stack_push(value);
        } break;

        case LSTORE: {
            u16 offset = read_u16(code, ip);
            i64 value = stack_pop();
            stack[fp - offset] = value;
        } break;

        case REFSTORE: {

        } break;

        case REFLOAD: {

        } break;

        case PUSH8: {
            u8 value = read_u8(code, ip);
            stack_push(value);
        } break;

        case PUSH16: {
            u16 value = read_u16(code, ip);
            stack_push(value);
        } break;

        case PUSH32: {
            u32 value = read_u32(code, ip);
            stack_push(value);
        } break;

        case PUSH64: {
            u64 value = read_u64(code, ip);
            stack_push(value);
        } break;

        case POP:
            stack_pop();
            break;

        case POP2:
            stack_pop();
            stack_pop();
            break;

        case DUP:
            // Duplicate the top value
            stack_push(stack_top());
            break;

        case DUP2:
            // Duplicate the top stack value twice.
            stack_push(stack_top());
            stack_push(stack_top());
            break;

        // How should we pass arguments to the functions
        // Currently we pass them on the stack but this poses a problem of stack manipulation.
        // IE. Perhaps the used the very last arg passed first and so on.
        // Since the first arg is on the top of the stack and the last below all of the other arguments.
        // 								stack load, stack store
        // Perhaps we have some sort of sload, sstore
        // This might address the stack with an offset
        // So we can use a stack value at say offset-4

        case CALL: {
            u16 index = read_u16(code, ip);
            u16 arg_count = read_u16(code, ip);

            printf("pre invoke fp=%lli, sp=%lli\n", fp, sp);

            fp = sp;

            stack_push(fp);
            stack_push(sp);

            invoke(*methods[index]);

            printf("post invoke fp=%lli, sp=%lli\n", fp, sp);

        } break;

        case RET: {

            i64 value = stack_pop();

            sp = stack_pop();
            fp = stack_pop();

            stack_push(value);

            printf("post return fp=%lli, sp=%lli\n", fp, sp);
        } break;

        case JMP:
            ip = read_u16(code, ip);
            break;

        case LJMP:
            ip = read_u32(code, ip);
            break;

        case JE: {
            i64 result = stack_pop();
            u64 address = read_u32(code, ip);
            if (result == 0) {
                ip = address;
            }
        } break;

        case JNE:  {
            i64 result = stack_pop();
            u64 address = read_u32(code, ip);
            if (result != 0) {
                ip = address;
            }
        } break;

        case JL: {
            i64 result = stack_pop();
            u64 address = read_u32(code, ip);
            if (result == -1) {
                ip = address;
            }
        } break;

        case JLE: {
            i64 result = stack_pop();
            u64 address = read_u32(code, ip);
            if (result == 0 || result == -1) {
                ip = address;
            }
        } break;

        case JG: {
            i64 result = stack_pop();
            u64 address = read_u32(code, ip);
            if (result == 1) {
                ip = address;
            }
        } break;

        case JGE: {
            i64 result = stack_pop();
            u64 address = read_u32(code, ip);
            if (result == 0 || result == 1) {
                ip = address;
            }
        } break;

        case CMP: {
            u8 type = read_u8(code, ip);

            switch (type) {

            case type_null: break;

            case type_u8: {
                u8 lhs = (u8)stack_pop();
                u8 rhs = (u8)stack_pop();
                if (lhs < rhs) stack_push(-1);
                else if (lhs > rhs) stack_push(1);
                else stack_push(0);
            } break;

            case type_u16: {
                u16 lhs = (u16)stack_pop();
                u16 rhs = (u16)stack_pop();
                if (lhs < rhs) stack_push(-1);
                else if (lhs > rhs) stack_push(1);
                else stack_push(0);
            } break;

            case type_u32: {
                u32 lhs = (u32)stack_pop();
                u32 rhs = (u32)stack_pop();
                if (lhs < rhs) stack_push(-1);
                else if (lhs > rhs) stack_push(1);
                else stack_push(0);
            } break;

            case type_u64: {
                u64 lhs = (u64)stack_pop();
                u64 rhs = (u64)stack_pop();
                if (lhs < rhs) stack_push(-1);
                else if (lhs > rhs) stack_push(1);
                else stack_push(0);
            } break;

            case type_i8: {
                i8 lhs = (i8)stack_pop();
                i8 rhs = (i8)stack_pop();
                if (lhs < rhs) stack_push(-1);
                else if (lhs > rhs) stack_push(1);
                else stack_push(0);
            } break;

            case type_i16: {
                i16 lhs = (i16)stack_pop();
                i16 rhs = (i16)stack_pop();
                if (lhs < rhs) stack_push(-1);
                else if (lhs > rhs) stack_push(1);
                else stack_push(0);
            } break;

            case type_i32: {
                i32 lhs = (i32)stack_pop();
                i32 rhs = (i32)stack_pop();
                if (lhs < rhs) stack_push(-1);
                else if (lhs > rhs) stack_push(1);
                else stack_push(0);
            } break;

            case type_i64: {
                i64 lhs = (i64)stack_pop();
                i64 rhs = (i64)stack_pop();
                if (lhs < rhs) stack_push(-1);
                else if (lhs > rhs) stack_push(1);
                else stack_push(0);
            } break;

            case type_r32: {
                r32 lhs = (r32)stack_pop();
                r32 rhs = (r32)stack_pop();
                if (lhs < rhs) stack_push(-1);
                else if (lhs > rhs) stack_push(1);
                else stack_push(0);
            } break;

            case type_r64: {
                r64 lhs = (r64)stack_pop();
                r64 rhs = (r64)stack_pop();
                if (lhs < rhs) stack_push(-1);
                else if (lhs > rhs) stack_push(1);
                else stack_push(0);
            } break;

            } // switch (type)
        } break;

        case ADD: {
            u8 type = read_u8(code, ip);

            switch (type) {

            case type_null: break;

            case type_u8: {
                u8 lhs = (u8)stack_pop();
                u8 rhs = (u8)stack_pop();
                u8 result = lhs + rhs;
                stack_push(result);
            } break;

            case type_u16: {
                u16 lhs = (u16)stack_pop();
                u16 rhs = (u16)stack_pop();
                u16 result = lhs + rhs;
                stack_push(result);
            } break;

            case type_u32: {
                u32 lhs = (u32)stack_pop();
                u32 rhs = (u32)stack_pop();
                u32 result = lhs + rhs;
                stack_push(result);
            } break;

            case type_u64: {
                u64 lhs = (u64)stack_pop();
                u64 rhs = (u64)stack_pop();
                u64 result = lhs + rhs;
                stack_push(result);
            } break;

            case type_i8: {
                i8 lhs = (i8)stack_pop();
                i8 rhs = (i8)stack_pop();
                i8 result = lhs + rhs;
                stack_push(result);
            } break;

            case type_i16: {
                i16 lhs = (i16)stack_pop();
                i16 rhs = (i16)stack_pop();
                i16 result = lhs + rhs;
                stack_push(result);
            } break;

            case type_i32: {
                i32 lhs = (i32)stack_pop();
                i32 rhs = (i32)stack_pop();
                i32 result = lhs + rhs;
                stack_push(result);
            } break;

            case type_i64: {
                i64 lhs = (i64)stack_pop();
                i64 rhs = (i64)stack_pop();
                i64 result = lhs + rhs;
                stack_push(result);
            } break;

            case type_r32: {
                r32 lhs = to_r32((i32)stack_pop());
                r32 rhs = to_r32((i32)stack_pop());
                r32 result = lhs + rhs;
                stack_push(to_i32(result));
            } break;

            case type_r64: {
                r64 lhs = to_r64(stack_pop());
                r64 rhs = to_r64(stack_pop());
                r64 result = lhs + rhs;
                stack_push(to_i64(result));
            } break;

            } // switch (type)
        } break;

        case SUB: {
            u8 type = read_u8(code, ip);

            switch (type) {

            case type_null: break;

            case type_u8: {
                u8 lhs = (u8)stack_pop();
                u8 rhs = (u8)stack_pop();
                u8 result = lhs - rhs;
                stack_push(result);
            } break;

            case type_u16: {
                u16 lhs = (u16)stack_pop();
                u16 rhs = (u16)stack_pop();
                u16 result = lhs - rhs;
                stack_push(result);
            } break;

            case type_u32: {
                u32 lhs = (u32)stack_pop();
                u32 rhs = (u32)stack_pop();
                u32 result = lhs - rhs;
                stack_push(result);
            } break;

            case type_u64: {
                u64 lhs = (u64)stack_pop();
                u64 rhs = (u64)stack_pop();
                u64 result = lhs - rhs;
                stack_push(result);
            } break;

            case type_i8: {
                i8 lhs = (i8)stack_pop();
                i8 rhs = (i8)stack_pop();
                i8 result = lhs - rhs;
                stack_push(result);
            } break;

            case type_i16: {
                i16 lhs = (i16)stack_pop();
                i16 rhs = (i16)stack_pop();
                i16 result = lhs + rhs;
                stack_push(result);
            } break;

            case type_i32: {
                i32 lhs = (i32)stack_pop();
                i32 rhs = (i32)stack_pop();
                i32 result = lhs - rhs;
                stack_push(result);
            } break;

            case type_i64: {
                i64 lhs = (i64)stack_pop();
                i64 rhs = (i64)stack_pop();
                i64 result = lhs - rhs;
                stack_push(result);
            } break;

            case type_r32: {
                r32 lhs = to_r32((i32)stack_pop());
                r32 rhs = to_r32((i32)stack_pop());
                r32 result = lhs - rhs;
                stack_push(to_i32(result));
            } break;

            case type_r64: {
                r64 lhs = to_r64(stack_pop());
                r64 rhs = to_r64(stack_pop());
                r64 result = lhs - rhs;
                stack_push(to_i64(result));
            } break;

            } // switch (type)
        } break;

        case MUL: {
            u8 type = read_u8(code, ip);

            switch (type) {

            case type_null: break;

            case type_u8: {
                u8 lhs = (u8)stack_pop();
                u8 rhs = (u8)stack_pop();
                u8 result = lhs * rhs;
                stack_push(result);
            } break;

            case type_u16: {
                u16 lhs = (u16)stack_pop();
                u16 rhs = (u16)stack_pop();
                u16 result = lhs * rhs;
                stack_push(result);
            } break;

            case type_u32: {
                u32 lhs = (u32)stack_pop();
                u32 rhs = (u32)stack_pop();
                u32 result = lhs * rhs;
                stack_push(result);
            } break;

            case type_u64: {
                u64 lhs = (u64)stack_pop();
                u64 rhs = (u64)stack_pop();
                u64 result = lhs * rhs;
                stack_push(result);
            } break;

            case type_i8: {
                i8 lhs = (i8)stack_pop();
                i8 rhs = (i8)stack_pop();
                i8 result = lhs * rhs;
                stack_push(result);
            } break;

            case type_i16: {
                i16 lhs = (i16)stack_pop();
                i16 rhs = (i16)stack_pop();
                i16 result = lhs * rhs;
                stack_push(result);
            } break;

            case type_i32: {
                i32 lhs = (i32)stack_pop();
                i32 rhs = (i32)stack_pop();
                i32 result = lhs * rhs;
                stack_push(result);
            } break;

            case type_i64: {
                i64 lhs = (i64)stack_pop();
                i64 rhs = (i64)stack_pop();
                i64 result = lhs * rhs;
                stack_push(result);
            } break;

            case type_r32: {
                r32 lhs = to_r32((i32)stack_pop());
                r32 rhs = to_r32((i32)stack_pop());
                r32 result = lhs * rhs;
                stack_push(to_i32(result));
            } break;

            case type_r64: {
                r64 lhs = to_r64(stack_pop());
                r64 rhs = to_r64(stack_pop());
                r64 result = lhs * rhs;
                stack_push(to_i64(result));
            } break;

            } // switch (type)
        } break;

        case DIV: {
            u8 type = read_u8(code, ip);

            switch (type) {

            case type_null: break;

            case type_u8: {
                u8 lhs = (u8)stack_pop();
                u8 rhs = (u8)stack_pop();
                u8 result = lhs / rhs;
                stack_push(result);
            } break;

            case type_u16: {
                u16 lhs = (u16)stack_pop();
                u16 rhs = (u16)stack_pop();
                u16 result = lhs / rhs;
                stack_push(result);
            } break;

            case type_u32: {
                u32 lhs = (u32)stack_pop();
                u32 rhs = (u32)stack_pop();
                u32 result = lhs / rhs;
                stack_push(result);
            } break;

            case type_u64: {
                u64 lhs = (u64)stack_pop();
                u64 rhs = (u64)stack_pop();
                u64 result = lhs / rhs;
                stack_push(result);
            } break;

            case type_i8: {
                i8 lhs = (i8)stack_pop();
                i8 rhs = (i8)stack_pop();
                i8 result = lhs / rhs;
                stack_push(result);
            } break;

            case type_i16: {
                i16 lhs = (i16)stack_pop();
                i16 rhs = (i16)stack_pop();
                i16 result = lhs / rhs;
                stack_push(result);
            } break;

            case type_i32: {
                i32 lhs = (i32)stack_pop();
                i32 rhs = (i32)stack_pop();
                i32 result = lhs / rhs;
                stack_push(result);
            } break;

            case type_i64: {
                i64 lhs = (i64)stack_pop();
                i64 rhs = (i64)stack_pop();
                i64 result = lhs / rhs;
                stack_push(result);
            } break;

            case type_r32: {
                r32 lhs = to_r32((i32)stack_pop());
                r32 rhs = to_r32((i32)stack_pop());
                r32 result = lhs / rhs;
                stack_push(to_i32(result));
            } break;

            case type_r64: {
                r64 lhs = to_r64(stack_pop());
                r64 rhs = to_r64(stack_pop());
                r64 result = lhs / rhs;
                stack_push(to_i64(result));
            } break;

            } // switch (type)
        } break;

        case MOD: {
            u8 type = read_u8(code, ip);

            switch (type) {

            case type_null: break;

            case type_u8: {
                u8 lhs = (u8)stack_pop();
                u8 rhs = (u8)stack_pop();
                u8 result = lhs % rhs;
                stack_push(result);
            } break;

            case type_u16: {
                u16 lhs = (u16)stack_pop();
                u16 rhs = (u16)stack_pop();
                u16 result = lhs % rhs;
                stack_push(result);
            } break;

            case type_u32: {
                u32 lhs = (u32)stack_pop();
                u32 rhs = (u32)stack_pop();
                u32 result = lhs % rhs;
                stack_push(result);
            } break;

            case type_u64: {
                u64 lhs = (u64)stack_pop();
                u64 rhs = (u64)stack_pop();
                u64 result = lhs % rhs;
                stack_push(result);
            } break;

            case type_i8: {
                i8 lhs = (i8)stack_pop();
                i8 rhs = (i8)stack_pop();
                i8 result = lhs % rhs;
                stack_push(result);
            } break;

            case type_i16: {
                i16 lhs = (i16)stack_pop();
                i16 rhs = (i16)stack_pop();
                i16 result = lhs % rhs;
                stack_push(result);
            } break;

            case type_i32: {
                i32 lhs = (i32)stack_pop();
                i32 rhs = (i32)stack_pop();
                i32 result = lhs % rhs;
                stack_push(result);
            } break;

            case type_i64: {
                i64 lhs = (i64)stack_pop();
                i64 rhs = (i64)stack_pop();
                i64 result = lhs % rhs;
                stack_push(result);
            } break;

            case type_r32: {
                r32 lhs = to_r32((i32)stack_pop());
                r32 rhs = to_r32((i32)stack_pop());
                r32 result = fmod(lhs, rhs);
                stack_push(to_i32(result));
            } break;

            case type_r64: {
                r64 lhs = to_r64(stack_pop());
                r64 rhs = to_r64(stack_pop());
                r64 result = fmod(lhs, rhs);
                stack_push(to_i64(result));
            } break;

            } // switch (type)
        } break;

        case BSL: {
            u8 type = read_u8(code, ip);

            switch (type) {

            case type_null: break;

            case type_u8: {
                u8 lhs = (u8)stack_pop();
                u8 rhs = (u8)stack_pop();
                u8 result = lhs << rhs;
                stack_push(result);
            } break;

            case type_u16: {
                u16 lhs = (u16)stack_pop();
                u16 rhs = (u16)stack_pop();
                u16 result = lhs << rhs;
                stack_push(result);
            } break;

            case type_u32: {
                u32 lhs = (u32)stack_pop();
                u32 rhs = (u32)stack_pop();
                u32 result = lhs << rhs;
                stack_push(result);
            } break;

            case type_u64: {
                u64 lhs = (u64)stack_pop();
                u64 rhs = (u64)stack_pop();
                u64 result = lhs << rhs;
                stack_push(result);
            } break;

            case type_i8: {
                i8 lhs = (i8)stack_pop();
                i8 rhs = (i8)stack_pop();
                i8 result = lhs << rhs;
                stack_push(result);
            } break;

            case type_i16: {
                i16 lhs = (i16)stack_pop();
                i16 rhs = (i16)stack_pop();
                i16 result = lhs << rhs;
                stack_push(result);
            } break;

            case type_i32: {
                i32 lhs = (i32)stack_pop();
                i32 rhs = (i32)stack_pop();
                i32 result = lhs << rhs;
                stack_push(result);
            } break;

            case type_i64: {
                i64 lhs = (i64)stack_pop();
                i64 rhs = (i64)stack_pop();
                i64 result = lhs << rhs;
                stack_push(result);
            } break;

            } // switch (type)
        } break;

        case BSR: {
            u8 type = read_u8(code, ip);

            switch (type) {

            case type_null: break;

            case type_u8: {
                u8 lhs = (u8)stack_pop();
                u8 rhs = (u8)stack_pop();
                u8 result = lhs >> rhs;
                stack_push(result);
            } break;

            case type_u16: {
                u16 lhs = (u16)stack_pop();
                u16 rhs = (u16)stack_pop();
                u16 result = lhs >> rhs;
                stack_push(result);
            } break;

            case type_u32: {
                u32 lhs = (u32)stack_pop();
                u32 rhs = (u32)stack_pop();
                u32 result = lhs >> rhs;
                stack_push(result);
            } break;

            case type_u64: {
                u64 lhs = (u64)stack_pop();
                u64 rhs = (u64)stack_pop();
                u64 result = lhs >> rhs;
                stack_push(result);
            } break;

            case type_i8: {
                i8 lhs = (i8)stack_pop();
                i8 rhs = (i8)stack_pop();
                i8 result = lhs >> rhs;
                stack_push(result);
            } break;

            case type_i16: {
                i16 lhs = (i16)stack_pop();
                i16 rhs = (i16)stack_pop();
                i16 result = lhs >> rhs;
                stack_push(result);
            } break;

            case type_i32: {
                i32 lhs = (i32)stack_pop();
                i32 rhs = (i32)stack_pop();
                i32 result = lhs >> rhs;
                stack_push(result);
            } break;

            case type_i64: {
                i64 lhs = (i64)stack_pop();
                i64 rhs = (i64)stack_pop();
                i64 result = lhs >> rhs;
                stack_push(result);
            } break;

            } // switch (type)
        } break;

        case NOT: {
            u8 type = read_u8(code, ip);

            switch (type) {

            case type_null: break;

            case type_u8: {
                u8 lhs = (u8)stack_pop();
                u8 result = !lhs;
                stack_push(result);
            } break;

            case type_u16: {
                u16 lhs = (u16)stack_pop();
                u16 result = !lhs;
                stack_push(result);
            } break;

            case type_u32: {
                u32 lhs = (u32)stack_pop();
                u32 result = !lhs;
                stack_push(result);
            } break;

            case type_u64: {
                u64 lhs = (u64)stack_pop();
                u64 result = !lhs;
                stack_push(result);
            } break;

            case type_i8: {
                i8 lhs = (i8)stack_pop();
                i8 result = !lhs;
                stack_push(result);
            } break;

            case type_i16: {
                i16 lhs = (i16)stack_pop();
                i16 result = !lhs;
                stack_push(result);
            } break;

            case type_i32: {
                i32 lhs = (i32)stack_pop();
                i32 result = !lhs;
                stack_push(result);
            } break;

            case type_i64: {
                i64 lhs = (i64)stack_pop();
                i64 result = !lhs;
                stack_push(result);
            } break;

            case type_r32: {
                r32 lhs = to_r32((i32)stack_pop());
                r32 result = !lhs;
                stack_push(to_i32(result));
            } break;

            case type_r64: {
                r64 lhs = to_r64(stack_pop());
                r64 result = !lhs;
                stack_push(to_i64(result));
            } break;

            } // switch (type)
        } break;

        case OR: {
            u8 type = read_u8(code, ip);

            switch (type) {

            case type_null: break;

            case type_u8: {
                u8 lhs = (u8)stack_pop();
                u8 rhs = (u8)stack_pop();
                u8 result = lhs | rhs;
                stack_push(result);
            } break;

            case type_u16: {
                u16 lhs = (u16)stack_pop();
                u16 rhs = (u16)stack_pop();
                u16 result = lhs | rhs;
                stack_push(result);
            } break;

            case type_u32: {
                u32 lhs = (u32)stack_pop();
                u32 rhs = (u32)stack_pop();
                u32 result = lhs | rhs;
                stack_push(result);
            } break;

            case type_u64: {
                u64 lhs = (u64)stack_pop();
                u64 rhs = (u64)stack_pop();
                u64 result = lhs | rhs;
                stack_push(result);
            } break;

            case type_i8: {
                i8 lhs = (i8)stack_pop();
                i8 rhs = (i8)stack_pop();
                i8 result = lhs | rhs;
                stack_push(result);
            } break;

            case type_i16: {
                i16 lhs = (i16)stack_pop();
                i16 rhs = (i16)stack_pop();
                i16 result = lhs | rhs;
                stack_push(result);
            } break;

            case type_i32: {
                i32 lhs = (i32)stack_pop();
                i32 rhs = (i32)stack_pop();
                i32 result = lhs | rhs;
                stack_push(result);
            } break;

            case type_i64: {
                i64 lhs = (i64)stack_pop();
                i64 rhs = (i64)stack_pop();
                i64 result = lhs | rhs;
                stack_push(result);
            } break;

            } // switch (type)
        } break;

        case XOR: {
            u8 type = read_u8(code, ip);

            switch (type) {

            case type_null: break;

            case type_u8: {
                u8 lhs = (u8)stack_pop();
                u8 rhs = (u8)stack_pop();
                u8 result = lhs ^ rhs;
                stack_push(result);
            } break;

            case type_u16: {
                u16 lhs = (u16)stack_pop();
                u16 rhs = (u16)stack_pop();
                u16 result = lhs ^ rhs;
                stack_push(result);
            } break;

            case type_u32: {
                u32 lhs = (u32)stack_pop();
                u32 rhs = (u32)stack_pop();
                u32 result = lhs ^ rhs;
                stack_push(result);
            } break;

            case type_u64: {
                u64 lhs = (u64)stack_pop();
                u64 rhs = (u64)stack_pop();
                u64 result = lhs ^ rhs;
                stack_push(result);
            } break;

            case type_i8: {
                i8 lhs = (i8)stack_pop();
                i8 rhs = (i8)stack_pop();
                i8 result = lhs ^ rhs;
                stack_push(result);
            } break;

            case type_i16: {
                i16 lhs = (i16)stack_pop();
                i16 rhs = (i16)stack_pop();
                i16 result = lhs ^ rhs;
                stack_push(result);
            } break;

            case type_i32: {
                i32 lhs = (i32)stack_pop();
                i32 rhs = (i32)stack_pop();
                i32 result = lhs ^ rhs;
                stack_push(result);
            } break;

            case type_i64: {
                i64 lhs = (i64)stack_pop();
                i64 rhs = (i64)stack_pop();
                i64 result = lhs ^ rhs;
                stack_push(result);
            } break;

            } // switch (type)
        } break;

        case INC: {
            u8 type = read_u8(code, ip);

            switch (type) {

            case type_null: break;

            case type_u8: {
                u8 lhs = (u8)stack_pop();
                u8 result = lhs + 1;
                stack_push(result);
            } break;

            case type_u16: {
                u16 lhs = (u16)stack_pop();
                u16 result = lhs + 1;
                stack_push(result);
            } break;

            case type_u32: {
                u32 lhs = (u32)stack_pop();
                u32 result = lhs + 1;
                stack_push(result);
            } break;

            case type_u64: {
                u64 lhs = (u64)stack_pop();
                u64 result = lhs + 1;
                stack_push(result);
            } break;

            case type_i8: {
                i8 lhs = (i8)stack_pop();
                i8 result = lhs + 1;
                stack_push(result);
            } break;

            case type_i16: {
                i16 lhs = (i16)stack_pop();
                i16 result = lhs + 1;
                stack_push(result);
            } break;

            case type_i32: {
                i32 lhs = (i32)stack_pop();
                i32 result = lhs + 1;
                stack_push(result);
            } break;

            case type_i64: {
                i64 lhs = (i64)stack_pop();
                i64 result = lhs + 1;
                stack_push(result);
            } break;

            case type_r32: {
                r32 lhs = to_r32((i32)stack_pop());
                r32 result = lhs + 1.f;
                stack_push(to_i32(result));
            } break;

            case type_r64: {
                r64 lhs = to_r64(stack_pop());
                r64 result = lhs + 1.f;
                stack_push(to_i64(result));
            } break;

            } // switch (type)
        } break;

        case DEC: {
            u8 type = read_u8(code, ip);

            switch (type) {

            case type_null: break;

            case type_u8: {
                u8 lhs = (u8)stack_pop();
                u8 result = lhs - 1;
                stack_push(result);
            } break;

            case type_u16: {
                u16 lhs = (u16)stack_pop();
                u16 result = lhs - 1;
                stack_push(result);
            } break;

            case type_u32: {
                u32 lhs = (u32)stack_pop();
                u32 result = lhs - 1;
                stack_push(result);
            } break;

            case type_u64: {
                u64 lhs = (u64)stack_pop();
                u64 result = lhs - 1;
                stack_push(result);
            } break;

            case type_i8: {
                i8 lhs = (i8)stack_pop();
                i8 result = lhs - 1;
                stack_push(result);
            } break;

            case type_i16: {
                i16 lhs = (i16)stack_pop();
                i16 result = lhs - 1;
                stack_push(result);
            } break;

            case type_i32: {
                i32 lhs = (i32)stack_pop();
                i32 result = lhs - 1;
                stack_push(result);
            } break;

            case type_i64: {
                i64 lhs = (i64)stack_pop();
                i64 result = lhs - 1;
                stack_push(result);
            } break;

            case type_r32: {
                r32 lhs = to_r32((i32)stack_pop());
                r32 result = lhs - 1.f;
                stack_push(to_i32(result));
            } break;

            case type_r64: {
                r64 lhs = to_r64(stack_pop());
                r64 result = lhs - 1.f;
                stack_push(to_i64(result));
            } break;

            } // switch (type)
        } break;
        } // switch

    } // while
}

} // namespace vc
} // namespace t

