#include <vc/basic/token.h>
namespace t {
namespace vc {

utf8 token_str(TokenKind kind) {
    switch (kind) {

// build a switch case with all of the token kinds
// simply return the stringified token.

#define TOKEN_KIND(name) \
    case TokenKind::name: return utf8(#name);
#include <vc/definitions/token_kinds.def>
#undef TOKEN_KIND
    default:
        return utf8("");
    }
}

utf8 token_symbol(TokenKind kind) {
    switch (kind) {

    case TokenKind::Amp: return utf8("&");
    case TokenKind::AmpAmp: return utf8("&&");
    case TokenKind::AmpEqual: return utf8("&=");
    case TokenKind::Arrow: return utf8("->");
    case TokenKind::At: return utf8("@");
    case TokenKind::Caret: return utf8("^");
    case TokenKind::CaretEqual: return utf8("^=");
    case TokenKind::Colon: return utf8(":");
    case TokenKind::ColonColon: return utf8("::");
    case TokenKind::Comma: return utf8(",");
    case TokenKind::Ellipsis: return utf8("...");
    case TokenKind::Equal: return utf8("=");
    case TokenKind::EqualEqual: return utf8("==");
    case TokenKind::Exclaim: return utf8("!");
    case TokenKind::ExclaimEqual: return utf8("!=");
    case TokenKind::Greater: return utf8(">");
    case TokenKind::GreaterEqual: return utf8(">=");
    case TokenKind::GreaterGreater: return utf8(">>");
    case TokenKind::GreaterGreaterEqual: return utf8(">>=");
    case TokenKind::Hash: return utf8("#");
    case TokenKind::HashAt: return utf8("#@");
    case TokenKind::HashHash: return utf8("##");
    case TokenKind::LBrace: return utf8("{");
    case TokenKind::Less: return utf8("<");
    case TokenKind::LessEqual: return utf8("<=");
    case TokenKind::LessLess: return utf8("<<");
    case TokenKind::LessLessEqual: return utf8("<<=");
    case TokenKind::LParen: return utf8("(");
    case TokenKind::LSquare: return utf8("[");
    case TokenKind::Minus: return utf8("-");
    case TokenKind::MinusEqual: return utf8("-=");
    case TokenKind::MinusMinus: return utf8("--");
    case TokenKind::Percent: return utf8("%");
    case TokenKind::PercentEqual: return utf8("%=");
    case TokenKind::PercentPercent: return utf8("%%");
    case TokenKind::Period: return utf8(".");
    case TokenKind::PeriodStar: return utf8(".*");
    case TokenKind::Pipe: return utf8("|");
    case TokenKind::PipeEqual: return utf8("|=");
    case TokenKind::PipePipe: return utf8("||");
    case TokenKind::Plus: return utf8("+");
    case TokenKind::PlusEqual: return utf8("+=");
    case TokenKind::PlusPlus: return utf8("++");
    case TokenKind::Question: return utf8("?");
    case TokenKind::RBrace: return utf8("}");
    case TokenKind::RParen: return utf8(")");
    case TokenKind::RSquare: return utf8("]");
    case TokenKind::Semi: return utf8(";");
    case TokenKind::Slash: return utf8("/");
    case TokenKind::SlashEqual: return utf8("/=");
    case TokenKind::Star: return utf8("*");
    case TokenKind::StarEqual: return utf8("*=");
    case TokenKind::Tilde: return utf8("~");
    case TokenKind::TildeEqual: return utf8("~=");
    default: return utf8("");
    }
}

bool token_is_operator(TokenKind kind) {
    switch (kind) {
    default: return false;
    case TokenKind::Amp:
    case TokenKind::AmpAmp:
    case TokenKind::AmpEqual:
    case TokenKind::Arrow:
    case TokenKind::Caret:
    case TokenKind::CaretEqual:
    case TokenKind::Colon:
    //case TokenKind::ColonColon:
    case TokenKind::Comma:
    case TokenKind::Ellipsis:
    case TokenKind::Equal:
    case TokenKind::EqualEqual:
    case TokenKind::Exclaim:
    case TokenKind::ExclaimEqual:
    case TokenKind::Greater:
    case TokenKind::GreaterEqual:
    case TokenKind::GreaterGreater:
    case TokenKind::GreaterGreaterEqual:
    case TokenKind::Less:
    case TokenKind::LessEqual:
    case TokenKind::LessLess:
    case TokenKind::LessLessEqual:
    case TokenKind::Minus:
    case TokenKind::MinusEqual:
    case TokenKind::MinusMinus:
    case TokenKind::Percent:
    case TokenKind::PercentEqual:
    case TokenKind::PercentPercent:
    case TokenKind::Period:
    case TokenKind::PeriodStar:
    case TokenKind::Pipe:
    case TokenKind::PipeEqual:
    case TokenKind::PipePipe:
    case TokenKind::Plus:
    case TokenKind::PlusEqual:
    case TokenKind::PlusPlus:
    case TokenKind::Question:
    case TokenKind::Slash:
    case TokenKind::SlashEqual:
    case TokenKind::Star:
    case TokenKind::StarEqual:
    case TokenKind::Tilde:
    case TokenKind::TildeEqual:
    case TokenKind::LParen:
    case TokenKind::RParen:
        return true;
    } // switch(kind)
}

bool token_is_compare(TokenKind kind) {
    switch (kind) {

    default: break;

    case TokenKind::EqualEqual:
    case TokenKind::Greater:
    case TokenKind::GreaterEqual:
    case TokenKind::Less:
    case TokenKind::LessEqual:
        return true;

    } // switch (kind)

    return false;
}

void token_print(Token* token) {
    if (!token)
        return;

    utf8 tok_str = token_str(token->kind);

    printf("%s '%s' ", tok_str.buffer, token->str.buffer);
    source_loc_print(token->loc);
    printf("\n");

}

} // namespace vc
} // namespace t
