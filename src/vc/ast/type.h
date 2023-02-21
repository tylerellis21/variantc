#ifndef VC_TYPE_H_INCLUDE
#define VC_TYPE_H_INCLUDE

#include <vc/basic/builtinkind.h>
#include <vc/basic/sourcelocation.h>

namespace vc {

struct Name;

enum class TypeKind {
    Null = 0,

    ArrayType,
    BuiltinType,
    DeclRefType,
    PointerType,
    //TemplateType
};

struct Type {
    TypeKind typeKind;
    SourceLocation sourceLocation;

    Type(TypeKind typeKind, SourceLocation sourceLocation) :
        typeKind(typeKind),
        sourceLocation(sourceLocation)
    { }
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
    Name name;

    DeclRefType(SourceLocation sourceLocation, Name name) :
        Type(TypeKind::DeclRefType, sourceLocation),
        name(name)
    { }
};

/*

struct TemplateType : Type {
    Name name;
    std::vector<Type*> types;

    TemplateType(SourceLocation sourceLocation, Name name, std::vector<Type*> types) :
        Type(TypeKind::TemplateType, sourceLocation),
        name(name),
        types(types)
    { }
};

*/

} // namespace vc

#endif // VC_TYPE_H_INCLUDE