#include <vc/lexer.h>
#include <vc/basic/file_buffer.h>
#include <vc/compiler.h>

#include <t/core/string.h>

#include <iostream>
#include <map>

namespace t {
namespace vc {

inline bool is_symbol(char c) {

    switch (c) {

    case ' ':
    case '!':
    case '"':
    case '#':
    case '$':
    case '%':
    case '&':
    case '\'':
    case '*':
    case '+':
    case '-':
    case ',':
    case '.':
    case '/':
    case '\\':
    case ':':
    case ';':
    case '>':
    case '<':
    case '=':
    case '@':
    case '?':
    case '[':
    case ']':
    case '^':
    case '_':
    case '`':
    case '{':
    case '}':
    case '|':
    case '~':
    case '(':
    case ')':
        return true;

    default:
        return false;
    }
}


static t::Map<utf8, TokenKind> token_map = {
//    {"abstract", TokenKind::Abstract},
//    {"as", TokenKind::As},
    {"auto", TokenKind::Auto},
    {"bool", TokenKind::Bool},
    {"break", TokenKind::Break},
    {"case", TokenKind::Case},
    {"cast", TokenKind::Cast},
    {"char", TokenKind::Char},

//    {"class", TokenKind::Class},
    {"const", TokenKind::Const},
    {"continue", TokenKind::Continue},
    {"default", TokenKind::Default},

    {"def", TokenKind::Def},
    {"undef", TokenKind::Undefine},

    {"delete", TokenKind::Delete},
    {"do", TokenKind::Do},
    {"else", TokenKind::Else},
    {"enum", TokenKind::Enum},
    {"explicit", TokenKind::Explicit},
    {"export", TokenKind::Export},
//    {"extends", TokenKind::Extends},
    {"extern", TokenKind::Extern},
    {"false", TokenKind::BooleanLiteral},
    {"for", TokenKind::For},
//    {"friend", TokenKind::Friend},
//    {"get", TokenKind::Get},
    {"goto", TokenKind::Goto},
    {"if", TokenKind::If},
//    {"implements", TokenKind::Implements},
    {"import", TokenKind::Import},
//    {"indexer", TokenKind::Indexer},
    {"inline", TokenKind::Inline},

    {"i8", TokenKind::Int8},
    {"i16", TokenKind::Int16},
    {"i32", TokenKind::Int32},
    {"i64", TokenKind::Int64},
    {"i128", TokenKind::Int128},
    {"i256", TokenKind::Int256},
    {"i512", TokenKind::Int512},

//    {"interface", TokenKind::Interface},
    {"istring", TokenKind::IString},
    {"namespace", TokenKind::Namespace},
    {"new", TokenKind::New},
    {"package", TokenKind::Package},
//    {"private", TokenKind::Private},
//    {"protected", TokenKind::Protected},
//    {"proc", TokenKind::Proc},
//    {"public", TokenKind::Public},

    {"r32", TokenKind::Real32},
    {"r64", TokenKind::Real64},
    {"r128", TokenKind::Real128},
    {"r256", TokenKind::Real256},
    {"r512", TokenKind::Real512},

    {"return", TokenKind::Return},
//    {"set", TokenKind::Set},
    {"signed", TokenKind::Signed},
    {"static", TokenKind::Static},
    //{"string", TokenKind::String},
    {"struct", TokenKind::Struct},
    {"switch", TokenKind::Switch},
    {"template", TokenKind::Template},
    {"this", TokenKind::This},
    {"true", TokenKind::BooleanLiteral},
    {"typedef", TokenKind::Typedef},

    {"u8", TokenKind::Uint8},
    {"u16", TokenKind::Uint16},
    {"u32", TokenKind::Uint32},
    {"u64", TokenKind::Uint64},
    {"u128", TokenKind::Uint128},
    {"u256", TokenKind::Uint256},
    {"u512", TokenKind::Uint512},

    {"utf8", TokenKind::Utf8},
    {"utf16", TokenKind::Utf16},
    {"utf32", TokenKind::Utf32},
    {"union", TokenKind::Union},
    {"unsigned", TokenKind::Unsigned},
    {"using", TokenKind::Using},
//    {"virtual", TokenKind::Virtual},
    {"volatile", TokenKind::Volatile},
    {"void", TokenKind::Void},
    {"while", TokenKind::While},
};

bool is_whitespace(char ch) {
    switch (ch) {
    case ' ':
    case '\t':
    case '\r':
    case '\n':
        return true;
    default:
        return false;
    }
}

bool Lexer::open() {
    behind = 0;
    offset = 0;

    next_char();

    src_loc = { 1, 1 };
    tok_loc = src_loc;

    return true;
}

bool Lexer::has_chars() {
    return offset <= fb->buffer_size;
}

bool Lexer::has_tokens() {
    return has_chars() || tok_stack.offset > 0;
}

void Lexer::next_char() {

    switch (current) {
    case '\t':
        src_loc.column += 4;
        break;
    case '\n':
        src_loc.column = 1;
        src_loc.line++;
        break;
    default:
        src_loc.column++;
        break;
    }


    u64 size = fb->buffer_size;

    behind = current;

    if (offset < size)
        current = fb->buffer[offset];
    else
        current = -1;

    if (offset + 1 < size)
        ahead = fb->buffer[offset + 1];
    else
        ahead = -1;

    offset++;
}

void Lexer::append() {
    tok_buffer.push((u8)current);
}

void Lexer::append_consume() {
    append();
    next_char();
}

void Lexer::construct_token(Token* token, TokenKind kind) {
    token->kind = kind;
    token->loc = tok_loc;
    token->str = std::move(tok_buffer.str());

    tok_buffer.clear();
}

void Lexer::lex_numeric(Token* token) {

    TokenKind found_kind = TokenKind::IntegerLiteral;

    while (has_chars()) {
        if (is_digit(current) || current == '-') {
            append_consume();
        }
        else if (current == '.' || current == 'f') {
            append_consume();
            found_kind = TokenKind::RealLiteral;
        }
        else
            break;
    }

    construct_token(token, found_kind);
}

void Lexer::lex_word(Token* token) {

    TokenKind found_kind = TokenKind::Identifier;

    bool can_number = false;

    while (has_chars()) {
        if (is_letter(current) || current == '_') {
            can_number = true;
            append_consume();
        }
        else if (is_digit(current) && can_number) {
            append_consume();
        }
        else
            break;
    }

    // TODO: Replace the token_map with t::map
    utf8 search_str = tok_buffer.str();

    token_map.search(search_str, &found_kind);


    construct_token(token, found_kind);
}

void Lexer::lex_operator(Token* token) {
    TokenKind found_operator = TokenKind::Unknown;

#define SET_BREAK(type) { found_operator = type; break; }
#define SET_APP_BREAK(type) { found_operator = type; append_consume(); break; }

    switch (current) {

    case '[': SET_APP_BREAK(TokenKind::LSquare);
    case ']': SET_APP_BREAK(TokenKind::RSquare);
    case '(': SET_APP_BREAK(TokenKind::LParen);
    case ')': SET_APP_BREAK(TokenKind::RParen);
    case '{': SET_APP_BREAK(TokenKind::LBrace);
    case '}': SET_APP_BREAK(TokenKind::RBrace);
    case '?': SET_APP_BREAK(TokenKind::Question);
    case ';': SET_APP_BREAK(TokenKind::Semi);
    case ',': SET_APP_BREAK(TokenKind::Comma);
    case '@': SET_APP_BREAK(TokenKind::At);

    case '&':
        append_consume();
        switch (current) {
        case '&': SET_APP_BREAK(TokenKind::AmpAmp);
        case '=': SET_APP_BREAK(TokenKind::AmpEqual);
        default: SET_BREAK(TokenKind::Amp);
        }
        break;

    case '~':
        append_consume();
        switch (current) {
        case '=': SET_APP_BREAK(TokenKind::TildeEqual);
        default: SET_BREAK(TokenKind::Tilde);
        }
        break;

    case '*':
        append_consume();
        switch (current) {
        case '=': SET_APP_BREAK(TokenKind::StarEqual);
        default: SET_BREAK(TokenKind::Star);
        }
        break;

    case '+':
        append_consume();
        switch (current) {
        case '+': SET_APP_BREAK(TokenKind::PlusPlus);
        case '=': SET_APP_BREAK(TokenKind::PlusEqual);
        default: SET_BREAK(TokenKind::Plus);
        }
        break;

    case '-':
        append_consume();
        switch (current) {
        case '-': SET_APP_BREAK(TokenKind::MinusMinus);
        case '=': SET_APP_BREAK(TokenKind::MinusEqual);
        case '>': {
            append_consume();
            if (current == '*') {
                SET_APP_BREAK(TokenKind::ArrowStar);
            }
            else
                SET_BREAK(TokenKind::Arrow);
        }
        default: SET_BREAK(TokenKind::Minus);
        }
        break;

    case '!':
        append_consume();
        switch (current) {
        case '=': SET_APP_BREAK(TokenKind::ExclaimEqual);
        default: SET_BREAK(TokenKind::Exclaim);
        }
        break;

    case '/':
        append_consume();
        switch (current) {
        case '=': SET_APP_BREAK(TokenKind::SlashEqual);
        default: SET_BREAK(TokenKind::Slash);
        }
        break;

    case '%':
        append_consume();
        switch (current) {
        case '=': SET_APP_BREAK(TokenKind::PercentEqual);
        default: SET_BREAK(TokenKind::Percent);
        }
        break;

    case '^':
        append_consume();
        switch (current) {
        case '=': SET_APP_BREAK(TokenKind::CaretEqual);
        default: SET_BREAK(TokenKind::Caret);
        }
        break;

    case '=':
        append_consume();
        switch (current) {
        case '=': SET_APP_BREAK(TokenKind::EqualEqual);
        default: SET_BREAK(TokenKind::Equal);
        }
        break;

    case '|':
        append_consume();
        switch (current) {
        case '|': SET_APP_BREAK(TokenKind::PipePipe);
        case '=': SET_APP_BREAK(TokenKind::PipeEqual);
        default: SET_BREAK(TokenKind::Pipe);
        }
        break;

    case '#':
        append_consume();
        switch (current) {
        case '#': SET_APP_BREAK(TokenKind::HashHash);
        case '@': SET_APP_BREAK(TokenKind::HashAt);
        default: SET_BREAK(TokenKind::Hash);
        }
        break;

    case ':':
        append_consume();
        switch (current) {
        case ':': SET_APP_BREAK(TokenKind::ColonColon);
        default: SET_BREAK(TokenKind::Colon);
        }
        break;

    case '<':
        append_consume();
        switch (current) {
        case '<': {
            append_consume();
            if (current == '=') {
                SET_APP_BREAK(TokenKind::LessLessEqual);
            }
            else
                SET_BREAK(TokenKind::LessLess);
        }
        case '=': SET_APP_BREAK(TokenKind::LessEqual);
        default: SET_BREAK(TokenKind::Less);
        }

    break;

    case '>':
        append_consume();
        switch (current) {
        case '>': {
            append_consume();
            if (current == '=') {
                SET_APP_BREAK(TokenKind::GreaterGreaterEqual);
            }
            else
                SET_BREAK(TokenKind::GreaterGreater);
        }
        case '=': SET_APP_BREAK(TokenKind::GreaterEqual);
        default: SET_BREAK(TokenKind::Greater);
        }

    break;

    case '.':
        append_consume();
        switch (current) {
        case '*': SET_APP_BREAK(TokenKind::PeriodStar);
        case '.':
            append_consume();
            if (current == '.') { SET_APP_BREAK(TokenKind::Ellipsis); }
            else {
                SET_BREAK(TokenKind::LexError);
            }
        default: SET_BREAK(TokenKind::Period);
        }

        break;

    default:
        SET_APP_BREAK(TokenKind::LexError);
    }

    return construct_token(token, found_operator);
}

void Lexer::lex_character_escape(Token* token) {

    // consume the escape slash '\'
    next_char();

    switch (current) {
    
    // feedform
    case 'f':
        next_char();
        tok_buffer.push('\f');
        break;
    // new line
    case 'n':
        next_char();
        tok_buffer.push('\n');
        break;
    // carriage return
    case 'r':
        next_char();
        tok_buffer.push('\r');
        break;
    // tab
    case 't':
        next_char();
        tok_buffer.push('\t');
        break;
    case 'v':
        next_char();
        tok_buffer.push('\v');
        break;
    case '"':
        next_char();
        tok_buffer.push('\"');
        break;
    case '\\':
        next_char();
        tok_buffer.push('\\');
        break;
    case '\'':
        next_char();
        tok_buffer.push('\'');
        break;
    case '\?':
        next_char();
        tok_buffer.push('\?');
        break;

    // TODO(Tyler): octal and hex escapes.
    }
}

void Lexer::lex_string(Token* token) {

    // consume the quote
    next_char();

    while (has_chars()) {
        if (current == '"')
            break;
        else if (current == '\\')
            lex_character_escape(token);
        else
            append_consume();
    }

    // consume the quote
    next_char();
    construct_token(token, TokenKind::StringLiteral);
}

void Lexer::lex_character(Token* token) {

    // consume the '
    next_char();

    switch (current) {
    case '\\':
        lex_character_escape(token);
        break;
    default:
        append_consume();
        break;
    }

    construct_token(token, TokenKind::CharacterLiteral);

    // consume the '
    next_char();
}

void Lexer::lex_single_line_comment() {

    // consume the '//'
    next_char();
    next_char();

    while (has_chars()) {
        if (current == '\n' || current == 0) {
            next_char();
            break;
        }
        else
            next_char();
    }
}

void Lexer::lex_multi_line_comment() {

    // consume the '/*'
    next_char();
    next_char();

    while (has_chars()) {
        if (current == '*' && ahead == '/')
            break;
        else if (current == '/' && ahead == '*')
            lex_multi_line_comment();
        else
            next_char();
    }

    // consume the '*/'
    next_char();
    next_char();
}

void Lexer::next_token(Token* token) {
    while (has_chars()) {

        char ch = current;

        // set the starting location for all tokens.
        tok_loc = src_loc;

        // consume any whitespace and continue the loop.
        if (is_whitespace(ch)) {
            next_char();
            continue;
        }
        else if (ch == '\'')
            return lex_character(token);
        else if (ch == '\"')
            return lex_string(token);
        else if (ch == '/' && ahead == '/')
            lex_single_line_comment();
        else if (ch == '/' && ahead == '*')
            lex_multi_line_comment();
        else if (is_digit(ch) || (ch == '-' && is_digit(ahead)))
            return lex_numeric(token);
        else if (is_letter(ch) || ch == '_')
            return lex_word(token);

        else if (is_symbol(ch))
            return lex_operator(token);
        else {
            std::cout << "failed to lex!" << std::endl;
            next_char();
            break;
        }
    }

    if (!has_chars()) {
        token->kind = TokenKind::EndOfFile;
        token->loc = { u32(-1), u32(-1) };
        token->str = utf8("EndOfFile");
    }
}

} // namespace vc
} // namespace t
