#ifndef VC_TOKEN_PRECEDENCE_H_INCLUDE
#define VC_TOKEN_PRECEDENCE_H_INCLUDE

#include <vc/basic/token.h>

namespace vc {

enum class TokenPrecedence  : i32 {
    Unknown         = 0,
    Comma           = 1,    // ,
    Assignment      = 2,    // =, *=, /=, %=, +=, -=, <<=, >>=, &=, ^=, |=
    Conditional     = 3,    // ?
    LogicalOr       = 4,    // ||
    LogicalAnd      = 5,    // &&
    InclusiveOr     = 6,    // |
    ExclusiveOr     = 7,    // ^
    And             = 8,    // &
    Equality        = 9,    // ==, !=
    Relational      = 10,   //  >=, <=, >, <
    Shift           = 11,   // <<, >>
    Additive        = 12,   // -, +
    Multiplicative  = 13,   // *, /, %
    PointerToMember = 14    // .*, ->*
};

TokenPrecedence getTokenPrecedence(TokenKind kind);

} // namespace vc

#endif // TOKEN_PRECEDENCE_H_INCLUDE
