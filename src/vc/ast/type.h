#ifndef VC_TYPE_H_INCLUDE
#define VC_TYPE_H_INCLUDE

#include <vc/basic/sourcelocation.h>

namespace vc {

struct Name;

enum class TypeKind {
    Null = 0,

    ArrayType,
    BuiltinType,
    DeclRefType,
    PointerType
};

struct Type {
    TypeKind typeKind;
    SourceLocation sourceLocation;

    Type(TypeKind typeKind, SourceLocation sourceLocation) :
        typeKind(typeKind),
        sourceLocation(sourceLocation)
    { }
};

enum class BuiltinKind {
    Null = 0,

    Void,
    Bool,

    Char,
    Rune,
    CStr,
    Utf8,
    Utf16,
    Utf32,

    U8,
    U16,
    U32,
    U64,
    U128,
    U245,
    U512,
    U1024,

    I8,
    I16,
    I32,
    I64,
    I128,
    I256,
    I512,
    I1024, 

    R8,
    R16,
    R32,
    R64,
    R128,
    R256,
    R512,
    R1024,

    Decimal
};

struct ArrayType : Type {
    Type* type;
    u64 length;

    ArrayType(SourceLocation sourceLocation, Type* type, u64 length) :
        Type(TypeKind::ArrayType, sourceLocation),
        type(type),
        length(length)
    { }
};


struct BuiltinType : Type {
    BuiltinKind builtinKind;
    
    BuiltinType(SourceLocation sourceLocation, BuiltinKind builtinKind) : 
        Type(TypeKind::BuiltinType, sourceLocation),
        builtinKind(builtinKind)
    { }
};

struct PointerType : Type {
    Type* type;

    PointerType(SourceLocation sourceLocation, Type* type) :
        Type(TypeKind::PointerType, sourceLocation),
        type(type)
    { }
};

struct DeclRefType : Type {
    Name* name;

    DeclRefType(SourceLocation sourceLocation, Name* name) :
        Type(TypeKind::DeclRefType, sourceLocation),
        name(name)
    { }
};

} // namespace vc

#endif // VC_TYPE_H_INCLUDE