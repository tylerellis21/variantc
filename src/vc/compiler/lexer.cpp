#include <vc/compiler/lexer.h>

#include <locale>
#include <iostream>

namespace vc {

bool Lexer::isMoreChars() {
    return offset <= fileBuffer.string.length();
}

void Lexer::nextChar() {
    switch (current) {
    case '\n':
        sourceLocation.column = 1;
        sourceLocation.line++;
    break;
    default:
        sourceLocation.column++;
        break;
    }

    prev = current;

    if (offset < fileBuffer.string.length()) {
        current = fileBuffer.string[offset];
    }
    else {
        current = -1;
    }

    if (offset + 1 < fileBuffer.string.length()) {
        next = fileBuffer.string[offset + 1];
    }
    else {
        next = -1;
    }

    offset++;
}

bool Lexer::open(std::string filePath) {

    if (!fileBuffer.load(filePath)) {
        return false;
    }

    this->offset = 0;
    this->current = 0;
    this->prev = 0;
    this->next = 0;

    nextChar();

    this->sourceLocation = SourceLocation{1, 1};

    return true;
}

void Lexer::nextToken(Token* token) {
    token->kind = TokenKind::Null;

    while (isMoreChars()) {

        // Save the starting point for the next token.
        tokenLocation = sourceLocation;

        // consume any whitespace, then retry the loop again.
        if (std::isspace(current)) {
            nextChar();
            continue;
        }
        // parse a single quoted character
        // eg: 'e'
        else if (current == '\'') {
            return lexCharacter(token);
        }
        // parse a double quoted string sequence
        // eg: "hello world"
        else if (current == '\"') {
            return lexString(token);
        }
        // parse a single line comment
        // eg: // this is a comment
        else if (current == '/' && next == '/') {
            // no return since comments don't produce tokens
            lexSingleLineComment();
        }
        // parse a multi line comment
        // eg: /* a multi line comment */
        else if (current == '/' && next == '*') {
            // no return since comments don't produce tokens
            lexMultiLineComment();
        }
        // parse a numeric digit
        // eg: 12345
        // eg: -1234
        // eg: 0b1010
        // eg: 0xFFFF
        // eg: 0777
        else if (std::isdigit(current) || (current == '-' && std::isdigit(next))) {
            return lexNumeric(token);
        }
        // parse a word
        // eg: _hello
        // eg: hello_world
        else if (std::isalnum(current) || current == '_') {
            return lexWord(token);
        }
        // parse an operator
        // eg: ->
        // eg: ++
        // eg: --
        else if (std::ispunct(current)) {
            return lexOperator(token);
        }
        else {
            std::cout << "failed to lex character: " << current << std::endl;
            break;
        }

    }
}

void Lexer::append() {
    sstream << current;
}

void Lexer::appendConsume() {
   append();
   nextChar();
}

void Lexer::constructToken(Token* token, TokenKind kind) {
    token->kind = kind;
    token->loc = tokenLocation;
    token->string = sstream.str();

    sstream.str(std::string());
    // who the fuck thought clear would only clear the error state....
    sstream.clear();
}

void Lexer::lexBinaryNumber(Token* token) {
    // binary numbers are prefixed with 0b or 0B

    // skip the prefix
    nextChar();
    nextChar();

    while (isMoreChars() && (current == '1' || current == '0')) {
        appendConsume();
    }

    constructToken(token, TokenKind::BinaryIntegerLiteral);
}

void Lexer::lexOctalNumber(Token* token) {
    // octal numbers are prefixed with 0
    // skip the prefix
    nextChar();

    while (isMoreChars() && current >= '0' && current <= '7') {
        appendConsume();
    }

    constructToken(token, TokenKind::OctalIntegerLiteral);
}

void Lexer::lexHexNumber(Token* token) {
    // hex numbers are prefixed with 0x or 0X

    // skip the prefix
    nextChar();
    nextChar();

    while (isMoreChars() && isxdigit(current)) {
        appendConsume();
    }

    constructToken(token, TokenKind::HexIntegerLiteral);
}

void Lexer::lexNumeric(Token* token) {
    // Hex numbers are prefixed with 0x
    if (current == '0' && next == 'x' ||
        current == '0' && next == 'X') {
        return lexHexNumber(token);
    }

    // Binary numbers are prefixed with 0b
    if (current == '0' && next == 'b' ||
        current == '0' && next == 'B') {
        return lexBinaryNumber(token);
    }

    // octal numbers are prefixed with 0777
    if (current == 0 && std::isdigit(next)) {
        return lexOctalNumber(token);
    }

    TokenKind numericType = TokenKind::IntegerLiteral;

    while (isMoreChars()) {
        if (std::isdigit(current) || current == '-') {
            appendConsume();
        }
        else if (current == '.' || current == 'f' || current == 'd') {
            numericType = TokenKind::RealLiteral;
            appendConsume();
        }
        else break;
    }

    constructToken(token, numericType);
}

void Lexer::lexWord(Token* token) {
    TokenKind tokenKind = TokenKind::Identifier;
    bool canHaveNumber = false;

    while (isMoreChars()) {
        if (std::isalnum(current) || current == '_') {
            canHaveNumber =  true;
            appendConsume();
        }
        else if (std::isdigit(current) && canHaveNumber) {
            appendConsume();
        }
        else {
            break;
        }
    }

    // Lookup the token string using the token map
    // If we have an entry, use the found token kind.
    {
        std::string str = sstream.str();

        vc::TokenMap::iterator iterator = tokenMap.find(str);

        if (iterator != tokenMap.end()) {
            tokenKind = iterator->second;
        }
    }

    constructToken(token, tokenKind);
}

void Lexer::lexOperator(Token* token) {
    TokenKind operatorKind = TokenKind::Null;

    #define SET_BREAK(tokenKind) { operatorKind = tokenKind; break; }
    #define SET_APP_BREAK(tokenKind) { operatorKind = tokenKind; appendConsume(); break; }

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
        appendConsume();
        switch (current) {
        case '&': SET_APP_BREAK(TokenKind::AmpAmp);
        case '=': SET_APP_BREAK(TokenKind::AmpEqual);
        default: SET_BREAK(TokenKind::Amp);
        }
        break;

    case '~':
        appendConsume();
        switch (current) {
        case '=': SET_APP_BREAK(TokenKind::TildeEqual);
        default: SET_BREAK(TokenKind::Tilde);
        }
        break;

    case '*':
        appendConsume();
        switch (current) {
        case '=': SET_APP_BREAK(TokenKind::StarEqual);
        default: SET_BREAK(TokenKind::Star);
        }
        break;

    case '+':
        appendConsume();
        switch (current) {
        case '+': SET_APP_BREAK(TokenKind::PlusPlus);
        case '=': SET_APP_BREAK(TokenKind::PlusEqual);
        default: SET_BREAK(TokenKind::Plus);
        }
        break;

    case '-':
        appendConsume();
        switch (current) {
        case '-': SET_APP_BREAK(TokenKind::MinusMinus);
        case '=': SET_APP_BREAK(TokenKind::MinusEqual);
        case '>': {
            appendConsume();
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
        appendConsume();
        switch (current) {
        case '=': SET_APP_BREAK(TokenKind::ExclaimEqual);
        default: SET_BREAK(TokenKind::Exclaim);
        }
        break;

    case '/':
        appendConsume();
        switch (current) {
        case '=': SET_APP_BREAK(TokenKind::SlashEqual);
        default: SET_BREAK(TokenKind::Slash);
        }
        break;

    case '%':
        appendConsume();
        switch (current) {
        case '=': SET_APP_BREAK(TokenKind::PercentEqual);
        default: SET_BREAK(TokenKind::Percent);
        }
        break;

    case '^':
        appendConsume();
        switch (current) {
        case '=': SET_APP_BREAK(TokenKind::CaretEqual);
        default: SET_BREAK(TokenKind::Caret);
        }
        break;

    case '=':
        appendConsume();
        switch (current) {
        case '=': SET_APP_BREAK(TokenKind::EqualEqual);
        default: SET_BREAK(TokenKind::Equal);
        }
        break;

    case '|':
        appendConsume();
        switch (current) {
        case '|': SET_APP_BREAK(TokenKind::PipePipe);
        case '=': SET_APP_BREAK(TokenKind::PipeEqual);
        default: SET_BREAK(TokenKind::Pipe);
        }
        break;

    case '#':
        appendConsume();
        switch (current) {
        case '#': SET_APP_BREAK(TokenKind::HashHash);
        case '@': SET_APP_BREAK(TokenKind::HashAt);
        default: SET_BREAK(TokenKind::Hash);
        }
        break;

    case ':':
        appendConsume();
        switch (current) {
        case ':': SET_APP_BREAK(TokenKind::ColonColon);
        default: SET_BREAK(TokenKind::Colon);
        }
        break;

    case '<':
        appendConsume();
        switch (current) {
        case '<': {
            appendConsume();
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
        appendConsume();
        switch (current) {
        case '>': {
            appendConsume();
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
        appendConsume();
        switch (current) {
        case '*': SET_APP_BREAK(TokenKind::PeriodStar);
        case '.':
            appendConsume();
            if (current == '.') { SET_APP_BREAK(TokenKind::Ellipsis); }
            else {
                break;
            }
        default: SET_BREAK(TokenKind::Period);
        }

        break;

    default:
        break;
    }

    return constructToken(token, operatorKind);
}

void Lexer::lexEscapeSequence(Token* token) {
    // consume the escaping slash '/'
    nextChar();

    switch (current) {
        // alert (beep, bell)
        case 'a': sstream.putback('\a'); break;
        // backspace
        case 'b': sstream.putback('\b'); break;
        // feedform
        case 'f': sstream.putback('\f'); break;
        // new line
        case 'n': sstream.putback('\n'); break;
        // carriage return
        case 'r': sstream.putback('\r'); break;
        // tab
        case 't': sstream.putback('\t'); break;
        case 'v': sstream.putback('\v'); break;
        // Is this correct?
        case '"': sstream.putback('\"'); break;
        case '\\': sstream.putback('\\'); break;
        case '\'': sstream.putback('\''); break;
        case '\?': sstream.putback('\?'); break;
    }

    // consume the escaped character.
    nextChar();
}

void Lexer::lexString(Token* token) {
    // consume the starting double quote
    nextChar();

    while (isMoreChars()) {
        if (current == '"') {
            break;
        }
        else if (current == '\\') {
            lexEscapeSequence(token);
        }
        else {
            appendConsume();
        }
    }

    // consume the closing double quote
    nextChar();

    constructToken(token, TokenKind::StringLiteral);
}

void Lexer::lexCharacter(Token* token) {
    // consume the opening single quote
    nextChar();

    switch (current) {
    case '\\':
        lexEscapeSequence(token);
        break;
    default:
        appendConsume();
        break;
    }

    // consume the closing single quote
    nextChar();

    constructToken(token, TokenKind::CharacterLiteral);
}

void Lexer::lexSingleLineComment() {
    // consume the leading forward slashes '//'
    nextChar();
    nextChar();

    while (isMoreChars()) {
        if (current == '\n' || current == 0) {
            nextChar();
            break;
        }
        else {
            nextChar();
        }
    }
}

void Lexer::lexMultiLineComment() {
    // consume the opening /*
    nextChar();
    nextChar();

    while (isMoreChars()) {
        if (current == '*' && next == '/') {
            break;
        }
        else if (current == '/' && next == '*') {
            lexMultiLineComment();
        }
        else {
            nextChar();
        }
    }

    // consume the closing */
    nextChar();
    nextChar();
}

} // namespace vc
