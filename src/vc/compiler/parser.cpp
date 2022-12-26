#include <vc/compiler/parser.h>
#include <vc/compiler/lexer.h>

namespace vc {

Parser::Parser(Lexer* lexer) {
    this->lexer = lexer;
}

bool Parser::valid() {
    return lexer->isMoreChars();
}


bool Parser::open() {
    return true;
}

}