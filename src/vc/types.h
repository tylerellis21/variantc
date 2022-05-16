#ifndef VC_TYPES_H_INCLUDE
#define VC_TYPES_H_INCLUDE

#ifdef _MSC_VER

typedef unsigned __int8 u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

typedef __int8 i8;
typedef __int16 i16;
typedef __int32 i32;
typedef __int64 i64;

#else

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

#endif

typedef float r32;
typedef double r64;

typedef i64 isize;
typedef u64 usize;

typedef u32 rune;

#endif // VC_TYPES_H_INCLUDE
