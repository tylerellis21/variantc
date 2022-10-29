#include <chrono>
#include <iostream>

#include <vc/compiler/lexer.h>

#include "../unit_test.h"

using namespace vc;
using namespace cpptest;

#define LEXER_OPEN(filePath) \
    Lexer lexer; \
    if (!lexer.open(filePath)) { \
        return false; \
    }

TEST(Lexer, Comments) {
    LEXER_OPEN("src/tests/lexer/comments.vc");

    Token token;
    lexer.nextToken(&token);

    TEST_ASSERT(token.kind == TokenKind::Null);
    TEST_ASSERT(lexer.isMoreChars() == false);

    return true;
}

TEST(Lexer, Numerics) {
    LEXER_OPEN("src/tests/lexer/numerics.vc");

    while (lexer.isMoreChars()) {
        Token token;
        lexer.nextToken(&token);
        std::cout << "Token: " << token << std::endl;
    }

    //TEST_ASSERT(token.kind == TokenKind::Identifier);
    //lexer.nextToken(&token);
    //TEST_ASSERT(token.kind == TokenKind::Identifier);
    //std::cout << "Token: " << token << std::endl;
    return true;
}

TEST(Lexer, Words) {
    return true;
}

TEST(Lexer, Operators) {
    return true;
}

TEST(Lexer, Symbols) {
    return true;
}

TEST(Lexer, EscapeSequences) {
    return true;
}

TEST(Lexer, Strings) {
    return true;
}

TEST(Lexer, Characters) {
    return true;
}

TEST(Lexer, SingleLineComments) {
    return true;
}

TEST(Lexer, MultiLineComments) {
    return true;
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