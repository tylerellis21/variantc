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

    // Boolean Literals
    {
        Token booleanLiterals[2];

        lexer.nextToken(&booleanLiterals[0]);
        TEST_ASSERT(booleanLiterals[0].kind == TokenKind::BooleanLiteral);

        lexer.nextToken(&booleanLiterals[1]);
        TEST_ASSERT(booleanLiterals[1].kind == TokenKind::BooleanLiteral);
    }

    // Character Literals
    {
        Token characterLiterals[2];

        lexer.nextToken(&characterLiterals[0]);
        TEST_ASSERT(characterLiterals[0].kind == TokenKind::CharacterLiteral);

        lexer.nextToken(&characterLiterals[1]);
        TEST_ASSERT(characterLiterals[1].kind == TokenKind::UnicodeLiteral);
    }

    // String Literals
    {
        Token stringLiterals[4];

        lexer.nextToken(&stringLiterals[0]);
        TEST_ASSERT(stringLiterals[0].kind == TokenKind::StringLiteral);
        TEST_ASSERT(stringLiterals[0].string == "hello");

        lexer.nextToken(&stringLiterals[1]);
        TEST_ASSERT(stringLiterals[1].kind == TokenKind::StringLiteral);
        TEST_ASSERT(stringLiterals[1].string == "hello world");

        lexer.nextToken(&stringLiterals[2]);
        TEST_ASSERT(stringLiterals[2].kind == TokenKind::StringLiteral);
        TEST_ASSERT(stringLiterals[2].string == "\nhello world\nhello world\n");

        lexer.nextToken(&stringLiterals[3]);
        TEST_ASSERT(stringLiterals[3].kind == TokenKind::StringLiteral);
        TEST_ASSERT(stringLiterals[3].string == "hello\nmulti\nline\nstring");
    }

    // TODO(@Tyler): Make some helper functions to clean this up
    // eg: TEST_TOKEN_KIND(TOKEN, EXPECTED_KIND)
    // eg: TEST_TOKEN_VALUE(TOKEN, EXPECTED_VALUE)

    // eg: TEST_TOKEN_KIND_ARRAY(TOKEN, EXPECTED_KIND)
    // eg: TEST_TOKEN_VALUE_ARRAY(TOKEN, EXPECTED_KIND)

    // Integer Literals
    {
        Token integerLiterals[2];

        lexer.nextToken(&integerLiterals[0]);
        TEST_ASSERT(integerLiterals[0].kind == TokenKind::IntegerLiteral);
        TEST_ASSERT(integerLiterals[0].string == "12345");

        lexer.nextToken(&integerLiterals[1]);
        TEST_ASSERT(integerLiterals[1].kind == TokenKind::IntegerLiteral);
        TEST_ASSERT(integerLiterals[1].string == "-12345");
    }

    // Hex Integer Literals
    {
        Token hexIntegerLiterals[3];

        lexer.nextToken(&hexIntegerLiterals[0]);
        TEST_ASSERT(hexIntegerLiterals[0].kind == TokenKind::HexIntegerLiteral);
        TEST_ASSERT(hexIntegerLiterals[0].string == "ffff");

        lexer.nextToken(&hexIntegerLiterals[1]);
        TEST_ASSERT(hexIntegerLiterals[1].kind == TokenKind::HexIntegerLiteral);
        TEST_ASSERT(hexIntegerLiterals[1].string == "FFFF");

        lexer.nextToken(&hexIntegerLiterals[2]);
        TEST_ASSERT(hexIntegerLiterals[2].kind == TokenKind::HexIntegerLiteral);
        TEST_ASSERT(hexIntegerLiterals[2].string == "0");
    }

    // Binary Integer Literals
    {
        Token binaryLiterals[2];

        lexer.nextToken(&binaryLiterals[0]);
        TEST_ASSERT(binaryLiterals[0].kind == TokenKind::BinaryIntegerLiteral);
        TEST_ASSERT(binaryLiterals[0].string == "00001111");

        lexer.nextToken(&binaryLiterals[1]);
        TEST_ASSERT(binaryLiterals[1].kind == TokenKind::BinaryIntegerLiteral);
        TEST_ASSERT(binaryLiterals[1].string == "11111111");

    }
    // Octal Integer Literals
    {
        Token octalIntegerLiteral[3];

        lexer.nextToken(&octalIntegerLiteral[0]);
        TEST_ASSERT(octalIntegerLiteral[0].kind == TokenKind::OctalIntegerLiteral);
        TEST_ASSERT(octalIntegerLiteral[0].string == "777");

        lexer.nextToken(&octalIntegerLiteral[1]);
        TEST_ASSERT(octalIntegerLiteral[1].kind == TokenKind::OctalIntegerLiteral);
        TEST_ASSERT(octalIntegerLiteral[1].string == "76543210");

        lexer.nextToken(&octalIntegerLiteral[2]);
        TEST_ASSERT(octalIntegerLiteral[2].kind == TokenKind::OctalIntegerLiteral);
        TEST_ASSERT(octalIntegerLiteral[2].string == "717");
    }

    // Real Literals
    {
        Token realLiterals[12];

        lexer.nextToken(&realLiterals[0]);
        TEST_ASSERT(realLiterals[0].kind == TokenKind::RealLiteral);
        TEST_ASSERT(realLiterals[0].string == "123.123");

        lexer.nextToken(&realLiterals[1]);
        TEST_ASSERT(realLiterals[1].kind == TokenKind::RealLiteral);
        TEST_ASSERT(realLiterals[1].string == "-123.123");

        lexer.nextToken(&realLiterals[2]);
        TEST_ASSERT(realLiterals[2].kind == TokenKind::RealLiteral);
        TEST_ASSERT(realLiterals[2].string == "0.0f");

        lexer.nextToken(&realLiterals[3]);
        TEST_ASSERT(realLiterals[3].kind == TokenKind::RealLiteral);
        TEST_ASSERT(realLiterals[3].string == "123.123f");

        lexer.nextToken(&realLiterals[4]);
        TEST_ASSERT(realLiterals[4].kind == TokenKind::RealLiteral);
        TEST_ASSERT(realLiterals[4].string == "123.f");

        lexer.nextToken(&realLiterals[5]);
        TEST_ASSERT(realLiterals[5].kind == TokenKind::RealLiteral);
        TEST_ASSERT(realLiterals[5].string == ".0f");

        lexer.nextToken(&realLiterals[6]);
        TEST_ASSERT(realLiterals[6].kind == TokenKind::RealLiteral);
        TEST_ASSERT(realLiterals[6].string == "-123.f");

        lexer.nextToken(&realLiterals[7]);
        TEST_ASSERT(realLiterals[7].kind == TokenKind::RealLiteral);
        TEST_ASSERT(realLiterals[7].string == "0.0");

        lexer.nextToken(&realLiterals[8]);
        TEST_ASSERT(realLiterals[8].kind == TokenKind::RealLiteral);
        TEST_ASSERT(realLiterals[8].string == "123.0d");

        lexer.nextToken(&realLiterals[9]);
        TEST_ASSERT(realLiterals[9].kind == TokenKind::RealLiteral);
        TEST_ASSERT(realLiterals[9].string == "-123.0d");

        lexer.nextToken(&realLiterals[10]);
        TEST_ASSERT(realLiterals[10].kind == TokenKind::RealLiteral);
        TEST_ASSERT(realLiterals[10].string == ".0d");

        lexer.nextToken(&realLiterals[11]);
        TEST_ASSERT(realLiterals[11].kind == TokenKind::RealLiteral);
        TEST_ASSERT(realLiterals[11].string == "-123.d");

    }

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