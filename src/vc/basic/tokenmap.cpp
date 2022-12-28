#include <vc/basic/tokenmap.h>

#define xstr(s) str(s)
#define str(s) #s

#define BUILTIN_KIND(x, y, z)

namespace vc {

// TOKEN_KIND()
// { "string", TokenKind::Kind },

/*
#define TYPE_TOKEN(TOKEN) { xstr(TOKEN), TokenKind::##TOKEN },
TYPE_TOKENS
#undef TYPE_TOKEN

// Generate an entry for each of the builtin types.
{ "i32", TokenKind::Int32 },

*/

const TokenMap tokenMap = {

    // Generate an entry for each of the builtin types.
    { "i32", TokenKind::Int32 },

    { "null", TokenKind::Null },
    { "align", TokenKind::Align },
    { "allocator", TokenKind::Allocator },
    { "as", TokenKind::As },
    { "async", TokenKind::Async },
    { "atomic", TokenKind::Atomic },
    { "attribute", TokenKind::Attribute },
    { "await", TokenKind::Await },
    { "base", TokenKind::Base },
    { "class", TokenKind::Class },
    { "const", TokenKind::Const },
    { "continue", TokenKind::Continue },
    { "def", TokenKind::Def },
    { "defer", TokenKind::Defer },
    { "delegate", TokenKind::Delegate },
    { "delete", TokenKind::Delete },
    { "do", TokenKind::Do },
    { "else", TokenKind::Else },
    { "enum", TokenKind::Enum },
    { "explicit", TokenKind::Explicit },
    { "export", TokenKind::Export },
    { "extern", TokenKind::Extern },
    { "false", TokenKind::BooleanLiteral },
    { "for", TokenKind::For },
    { "foreach", TokenKind::Foreach },
    { "goto", TokenKind::Goto },
    { "if", TokenKind::If },
    { "implicit", TokenKind::Implicit },
    { "import", TokenKind::Import },
    { "interface", TokenKind::Interface },
    { "lock", TokenKind::Lock },
    { "nameof", TokenKind::Nameof },
    { "namespace", TokenKind::Namespace },
    { "new", TokenKind::New },
    { "operator", TokenKind::Operator },
    { "package", TokenKind::Package },
    { "params", TokenKind::Params },
    { "return", TokenKind::Return },
    { "sizeof", TokenKind::Sizeof },
    { "static", TokenKind::Static },
    { "struct", TokenKind::Struct },
    { "switch", TokenKind::Switch },
    { "this", TokenKind::This },
    { "true", TokenKind::BooleanLiteral },
    { "typeof", TokenKind::Typeof },
    { "union", TokenKind::Union },
    { "use", TokenKind::Use },
    { "using", TokenKind::Using },
    { "void", TokenKind::Void },
    { "volatile", TokenKind::Volatile },
    { "while", TokenKind::While },
    { "yield", TokenKind::Yield },
};

}
