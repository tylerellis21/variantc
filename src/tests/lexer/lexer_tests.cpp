#include <vc/compiler/lexer.h>

bool test1() {

    Lexer lexer;
    if (!lexer.open("src/tests/lexer/basic.vc")) {
        return -1;
    }

    Token token;
    lexer.nextToken(&token);
    lexer.nextToken(&token);

    return true;
}