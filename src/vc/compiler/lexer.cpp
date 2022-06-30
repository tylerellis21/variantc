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

    sstream.str( std::string() );
    // who the fuck thought clear would only clear the error state....
    sstream.clear();
}

void Lexer::lexNumeric(Token* token) {
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

    std::string str = sstream.str();
    
    vc::TokenMap::iterator iterator = tokenMap.find(str);

    if (iterator != tokenMap.end()) {
        tokenKind = iterator->second;
    }

    constructToken(token, tokenKind);
}

void Lexer::lexOperator(Token* token) {

}

void Lexer::lexEscapeSequence(Token* token) {

}

void Lexer::lexString(Token* token) {

}

void Lexer::lexCharacter(Token* token) {

}

void Lexer::lexSingleLineComment() {

}

void Lexer::lexMultiLineComment() {

}

} // namespace vc
