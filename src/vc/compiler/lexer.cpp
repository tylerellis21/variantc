#include <vc/compiler/lexer.h>

namespace vc {

bool Lexer::isMoreChars() {
    return this->offset < fileBuffer.string.length();
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

}
