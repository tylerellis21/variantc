#include <vc/basic/token_precedence.h>

namespace t {
namespace vc {

prec::Level token_precedence(TokenKind kind) {
    switch (kind) {
    default:                              return prec::Level::Unknown;
    case TokenKind::Comma:                return prec::Level::Comma;
    case TokenKind::Equal:
    case TokenKind::StarEqual:
    case TokenKind::SlashEqual:
    case TokenKind::PercentEqual:
    case TokenKind::PlusEqual:
    case TokenKind::MinusEqual:
    case TokenKind::LessLessEqual:
    case TokenKind::GreaterGreaterEqual:
    case TokenKind::AmpEqual:
    case TokenKind::CaretEqual:
    case TokenKind::PipeEqual:            return prec::Level::Assignment;
    case TokenKind::Question:             return prec::Level::Conditional;
    case TokenKind::PipePipe:             return prec::Level::LogicalOr;
    case TokenKind::AmpAmp:               return prec::Level::LogicalAnd;
    case TokenKind::Pipe:                 return prec::Level::InclusiveOr;
    case TokenKind::Caret:                return prec::Level::ExclusiveOr;
    case TokenKind::Amp:                  return prec::Level::And;
    case TokenKind::ExclaimEqual:
    case TokenKind::EqualEqual:           return prec::Level::Equality;
    case TokenKind::LessEqual:
    case TokenKind::Less:
    case TokenKind::Greater:
    case TokenKind::GreaterEqual:         return prec::Level::Relational;
    case TokenKind::LessLess:             return prec::Level::Shift;
    case TokenKind::Plus:
    case TokenKind::Minus:                return prec::Level::Additive;
    case TokenKind::Percent:
    case TokenKind::Slash:
    case TokenKind::Star:                 return prec::Level::Multiplicative;
    case TokenKind::PeriodStar:
    //case TokenKind::Period:
    case TokenKind::ArrowStar:            return prec::Level::PointerToMember;
    } // switch (kind)
}

} // namespace vc
} // namespace t
