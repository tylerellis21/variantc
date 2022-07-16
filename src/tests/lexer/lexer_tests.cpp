#include <chrono>

#include <vc/compiler/lexer.h>

#include "../unit_test.h"

using namespace vc;

#define LEXER_OPEN(filePath) \
    Lexer lexer; \
    if (!lexer.open(filePath)) { \
        return false; \
    }

TEST(Lexer, BasicTokens) {
    LEXER_OPEN("src/tests/lexer/basic.vc");

    Token token;
    lexer.nextToken(&token);
       
    lexer.nextToken(&token);

    return true;
}

TEST(hello_world, testB) {
    return false;
}

/*

Lexer Tests Needed:
    Numerics
        Binary - base 1
        Octal - base 8
        Decimal - base10
        Hex - base16
    Words
    Operators & Symbols
    Escape Sequences
    Strings
    Chars
    Single Line Comments
    Multi Line Comments

*/