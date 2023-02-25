#include <vc/basic/builtinkind.h>

namespace vc {

BuiltinKind builtinKindFromTokenKind(TokenKind tokenKind) {
    switch (tokenKind) {
        #define BUILTIN_KIND(NAME, SYMBOL, SIZE) case TokenKind::##NAME: return BuiltinKind::##NAME;
        #include <vc/defs/builtin_kinds.inl>
        #undef BUILTIN_KIND
    default:
        return BuiltinKind::Null;
    }
}

std::string builtinKindString(BuiltinKind builtinKind) {
    switch (builtinKind) {
        #define BUILTIN_KIND(NAME, SYMBOL, SIZE) case BuiltinKind::##NAME: return std::string(#NAME);
        #include <vc/defs/builtin_kinds.inl>
        #undef BUILTIN_KIND
    default:
        return std::string("unhandled BuiltinKind");
    }
}

} // namespace vc