#ifndef TOKEN_PRECEDENCE_H_INCLUDE
#define TOKEN_PRECEDENCE_H_INCLUDE

#include <vc/basic/token.h>

namespace t {
namespace vc {

namespace prec {

enum Level {
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

} // namespace prec

prec::Level token_precedence(TokenKind kind);

} // namespace vc
} // namespace t

#endif // TOKEN_PRECEDENCE_H_INCLUDE
