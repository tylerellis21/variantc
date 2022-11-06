#include <chrono>
#include <iostream>

#include <vc/compiler/lexer.h>

#include "unit_test.h"

using namespace vc;
using namespace cpptest;

#define LEXER_OPEN(filePath) \
    Lexer lexer; \
    if (!lexer.open(filePath)) { \
        return false; \
    }

//TODO(@Tyler): Once we have string.join working replace theses full paths with a constant string base path of sorts.

TEST(Lexer, Comments) {
    LEXER_OPEN("src/tests/test-src/lexer/comments.vc");

    Token token;
    lexer.nextToken(&token);

    TEST_ASSERT(token.kind == TokenKind::Null);
    TEST_ASSERT(lexer.isMoreChars() == false);

    return true;
}

TEST(Lexer, Literals) {
    LEXER_OPEN("src/tests/test-src/lexer/literals.vc");

    Token booleanLiterals[2];

    lexer.nextToken(&booleanLiterals[0]);
    lexer.nextToken(&booleanLiterals[1]);

    TEST_ASSERT(booleanLiterals[0].kind == TokenKind::BooleanLiteral);
    TEST_ASSERT(booleanLiterals[1].kind == TokenKind::BooleanLiteral);

    Token characterLiterals[2];
    lexer.nextToken(&characterLiterals[0]);
    lexer.nextToken(&characterLiterals[1]);

    TEST_ASSERT(characterLiterals[0].kind == TokenKind::CharacterLiteral);
    TEST_ASSERT(characterLiterals[1].kind == TokenKind::UnicodeLiteral);

    Token stringLiterals[4];
    lexer.nextToken(&stringLiterals[0]);
    lexer.nextToken(&stringLiterals[1]);
    lexer.nextToken(&stringLiterals[2]);
    lexer.nextToken(&stringLiterals[3]);

    TEST_ASSERT(stringLiterals[0].kind == TokenKind::StringLiteral);
    TEST_ASSERT(stringLiterals[0].string == "hello");

    TEST_ASSERT(stringLiterals[1].kind == TokenKind::StringLiteral);
    TEST_ASSERT(stringLiterals[1].string == "hello world");

    TEST_ASSERT(stringLiterals[2].kind == TokenKind::StringLiteral);
    TEST_ASSERT(stringLiterals[2].string == "\nhello world\nhello world\n");

    TEST_ASSERT(stringLiterals[3].kind == TokenKind::StringLiteral);
    TEST_ASSERT(stringLiterals[3].string == "hello\nmulti\nline\nstring");

    // TODO(@Tyler): Make some helper functions to clean this up
    // eg: TEST_TOKEN_KIND(TOKEN, EXPECTED_KIND)
    // eg: TEST_TOKEN_VALUE(TOKEN, EXPECTED_VALUE)

    // eg: TEST_TOKEN_KIND_ARRAY(TOKEN, EXPECTED_KIND)
    // eg: TEST_TOKEN_VALUE_ARRAY(TOKEN, EXPECTED_KIND)
    Token integerLiterals[2];
    lexer.nextToken(&integerLiterals[0]);
    lexer.nextToken(&integerLiterals[1]);

    TEST_ASSERT(integerLiterals[0].kind == TokenKind::IntegerLiteral);
    TEST_ASSERT(integerLiterals[0].string == "12345");

    TEST_ASSERT(integerLiterals[1].kind == TokenKind::IntegerLiteral);
    TEST_ASSERT(integerLiterals[1].string == "-12345");

/*
(HexIntegerLiteral)
(BinaryIntegerLiteral)
(OctalIntegerLiteral)

(RealLiteral)
*/

    //TEST_ASSERT(token.kind == TokenKind::Identifier);
    //lexer.nextToken(&token);
    //TEST_ASSERT(token.kind == TokenKind::Identifier);
    //std::cout << "Token: " << token << std::endl;
    return true;
}

TEST(Lexer, Keywords) {
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