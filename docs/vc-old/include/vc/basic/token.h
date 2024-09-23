#ifndef TOKEN_H_INCLUDE
#define TOKEN_H_INCLUDE

#include <vc/basic/source_location.h>

#include <t/core/string.h>

namespace t {
namespace vc {

enum class TokenKind {
#define TOKEN_KIND(kind) kind,
#include <vc/definitions/token_kinds.def>
#undef TOKEN_KIND
};

struct Token {
    TokenKind kind;
    SourceLocation loc;
    utf8 str;

    inline Token() :
        kind(TokenKind::Unknown),
        loc({u32(-1), u32(-1)}),
        str() {
    }

    // Copy constructor
    inline Token(const Token& other) :
        kind(other.kind),
        loc(other.loc),
        str(other.str) {
    }

    // Copy assignment
    inline Token& operator=(const Token& other) {
        kind = other.kind;
        loc = other.loc;
        str = other.str;
        return *this;
    }

    // Move constructor
    inline Token(Token&& other) {
        swap(kind, other.kind);
        swap(loc, other.loc);
        swap(str, other.str);
    }

    // Move assignment
    inline Token& operator=(Token&& other) {
        if (this != &other) {
            swap(kind, other.kind);
            swap(loc, other.loc);
            swap(str, other.str);
        }
        return *this;
    }

    inline ~Token() { }
};

#define TYPE_TOKENS \
    TYPE_TOKEN(Int) \
    TYPE_TOKEN(Uint) \
    TYPE_TOKEN(Uptr) \
    TYPE_TOKEN(Char) \
    TYPE_TOKEN(Bool) \
    TYPE_TOKEN(Uint8) \
    TYPE_TOKEN(Uint16) \
    TYPE_TOKEN(Uint32) \
    TYPE_TOKEN(Uint64) \
    TYPE_TOKEN(Uint128) \
    TYPE_TOKEN(Uint256) \
    TYPE_TOKEN(Uint512) \
    TYPE_TOKEN(Int8) \
    TYPE_TOKEN(Int16) \
    TYPE_TOKEN(Int32) \
    TYPE_TOKEN(Int64) \
    TYPE_TOKEN(Int128) \
    TYPE_TOKEN(Int256) \
    TYPE_TOKEN(Int512) \
    TYPE_TOKEN(Void) \
    TYPE_TOKEN(Real32) \
    TYPE_TOKEN(Real64) \
    TYPE_TOKEN(Real128) \
    TYPE_TOKEN(Real256) \
    TYPE_TOKEN(Real512) \
    TYPE_TOKEN(Utf8) \
    TYPE_TOKEN(Utf16) \
    TYPE_TOKEN(Utf32)

utf8 token_str(TokenKind kind);
utf8 token_symbol(TokenKind kind);

inline utf8 token_symbol_or_string(TokenKind kind) {
    utf8 str = token_symbol(kind);
    // if there is no symbol use the name
    if (str.size == 0) str = token_str(kind);
    return str;
}

bool token_is_operator(TokenKind kind);
bool token_is_compare(TokenKind kind);

void token_print(Token* token);

} // namespace vc
} // namespace t

#endif // TOKEN_H_INCLUDE
