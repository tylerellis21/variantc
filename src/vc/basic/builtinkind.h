#ifndef VC_BUILTIN_KIND_H_INCLUDE
#define VC_BUILTIN_KIND_H_INCLUDE

namespace vc {

enum class BuiltinKind {
    #define BUILTIN_KIND(NAME, SYMBOL, SIZE) NAME,
    #include <vc/defs/builtin_kinds.inl>
    #undef BUILTIN_KIND
};

} // namespace vc

#endif // VC_BUILTIN_KIND_H_INCLUDE