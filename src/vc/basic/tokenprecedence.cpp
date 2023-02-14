#include <vc/basic/tokenprecedence.h>


namespace vc {

TokenPrecedence getTokenPrecedence(TokenKind kind) {
    switch (kind) {
    default:                              return TokenPrecedence::Unknown;
    case TokenKind::Comma:                return TokenPrecedence::Comma;
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
    case TokenKind::PipeEqual:            return TokenPrecedence::Assignment;
    case TokenKind::Question:             return TokenPrecedence::Conditional;
    case TokenKind::PipePipe:             return TokenPrecedence::LogicalOr;
    case TokenKind::AmpAmp:               return TokenPrecedence::LogicalAnd;
    case TokenKind::Pipe:                 return TokenPrecedence::InclusiveOr;
    case TokenKind::Caret:                return TokenPrecedence::ExclusiveOr;
    case TokenKind::Amp:                  return TokenPrecedence::And;
    case TokenKind::ExclaimEqual:
    case TokenKind::EqualEqual:           return TokenPrecedence::Equality;
    case TokenKind::LessEqual:
    case TokenKind::Less:
    case TokenKind::Greater:
    case TokenKind::GreaterEqual:         return TokenPrecedence::Relational;
    case TokenKind::LessLess:             return TokenPrecedence::Shift;
    case TokenKind::Plus:
    case TokenKind::Minus:                return TokenPrecedence::Additive;
    case TokenKind::Percent:
    case TokenKind::Slash:
    case TokenKind::Star:                 return TokenPrecedence::Multiplicative;
    case TokenKind::PeriodStar:
    //case TokenKind::Period:
    case TokenKind::ArrowStar:            return TokenPrecedence::PointerToMember;
    } // switch (kind)
}

} // namespace vc