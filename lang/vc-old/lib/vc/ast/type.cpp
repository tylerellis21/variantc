#include <vc/ast/type.h>

namespace t {
namespace vc {

BasicKind basic_from_token(TokenKind kind) {
    switch (kind) {

#define BASIC_KIND(KIND, STR, SIZE) case TokenKind::KIND: return BasicKind::KIND;
#include <vc/definitions/basic_kinds.def>
#undef BASIC_KIND

    default: return BasicKind::Empty;
    }
}

utf8 basic_kind_str(BasicKind kind) {
    switch (kind) {
    default: return utf8("");
#define BASIC_KIND(KIND, STR, SIZE) \
    case BasicKind::KIND: return utf8(#STR);
#include <vc/definitions/basic_kinds.def>
#undef BASIC_KIND
    }
}

i64 basic_kind_size(BasicKind kind) {
    switch (kind) {
    default: return 0;
#define BASIC_KIND(KIND, STR, SIZE) \
    case BasicKind::KIND: return SIZE;
#include <vc/definitions/basic_kinds.def>
#undef BASIC_KIND
    }
}

bool is_type_token(TokenKind kind) {
    switch (kind) {

#define BASIC_KIND(KIND, STR, SIZE) case TokenKind::KIND:
#include <vc/definitions/basic_kinds.def>
#undef BASIC_KIND

    case TokenKind::Less:
    case TokenKind::LSquare:
    case TokenKind::Star:
    case TokenKind::Ellipsis: return true;

    default: return false;
    }
}

bool type_compare(Type* lhs, Type* rhs) {

    if (lhs->kind != rhs->kind) return false;

    switch (lhs->kind) {

    // All array types have a size and a type
    // Both must match to be equal to each other.
    case TypeKind::ArrayType: {
        ArrayType* a_lhs = static_cast<ArrayType*>(lhs);
        ArrayType* a_rhs = static_cast<ArrayType*>(rhs);

        if (a_lhs->length != a_rhs->length) return false;

        return type_compare(a_lhs->type, a_rhs->type);
    }

    case TypeKind::BasicType: {
        BasicType* a_lhs = static_cast<BasicType*>(lhs);
        BasicType* a_rhs = static_cast<BasicType*>(rhs);

        return a_lhs->basic_kind == a_rhs->basic_kind;
    }

    case TypeKind::DeclRefType: {
        DeclRefType* a_lhs = static_cast<DeclRefType*>(lhs);
        DeclRefType* a_rhs = static_cast<DeclRefType*>(rhs);

        return name_compare(a_lhs->name, a_rhs->name);
    }

    case TypeKind::PointerType: {
        PointerType* a_lhs = static_cast<PointerType*>(lhs);
        PointerType* a_rhs = static_cast<PointerType*>(rhs);

        // Since each type is equal, we know they are both pointer types
        // just compare the base type.
        return type_compare(a_lhs->base, a_rhs->base);
    }

    // Template types are a bit more complex but in most cases they are easy to compare
    case TypeKind::TemplateType: {
        TemplateType* a_lhs = static_cast<TemplateType*>(lhs);
        TemplateType* a_rhs = static_cast<TemplateType*>(rhs);

        if (!name_compare(a_lhs->name, a_rhs->name)) return false;

        // TODO: compare logic
        if (a_lhs->types.count != a_rhs->types.count) return false;

        u64 count = a_lhs->types.count;
        for (u64 i = 0; i < count; i++) {
            if (!type_compare(a_lhs->types[i], a_rhs->types[i])) return false;
        }

        // If we reached here all the types in the template type list are the same
        // so we must have the same template type.
        return true;
    }

    case TypeKind::VarArgType: {

    }

    default: return false;

    } // switch (lhs->kind)
}

} // namespace vc
} // namespace t
