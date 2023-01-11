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

} // namespace vc