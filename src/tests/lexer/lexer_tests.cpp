#include <vc/compiler/lexer.h>

#define LEXER_OPEN(filePath) \
    Lexer lexer; \
    if (!lexer.open(filePath)) { \
        return false; \
    } \

bool test1() {

    LEXER_OPEN("src/tests/lexer/basic.vc");

    Token token;
    lexer.nextToken(&token);
    lexer.nextToken(&token);

    return true;
}