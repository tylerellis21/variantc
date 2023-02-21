#include "../lexer_shared.h"

TEST(Lexer, BooleanLiterals) {
    LEXER_OPEN("src/tests/test_src/lexer/literals/boolean_literals.vc");

    Token booleanLiterals[2];

    lexer.nextToken(&booleanLiterals[0]);
    TEST_ASSERT(booleanLiterals[0].kind == TokenKind::BooleanLiteral);

    lexer.nextToken(&booleanLiterals[1]);
    TEST_ASSERT(booleanLiterals[1].kind == TokenKind::BooleanLiteral);

    return true;
}

TEST(Lexer, CharacterLiterals) {
    LEXER_OPEN("src/tests/test_src/lexer/literals/character_literals.vc");

    Token characterLiterals[2];

    lexer.nextToken(&characterLiterals[0]);
    TEST_ASSERT(characterLiterals[0].kind == TokenKind::CharacterLiteral);
    TEST_ASSERT(characterLiterals[0].string == "a");

    lexer.nextToken(&characterLiterals[1]);
    TEST_ASSERT(characterLiterals[1].kind == TokenKind::UnicodeLiteral);
    TEST_ASSERT(characterLiterals[1].string == "2200");

    return true;
}

TEST(Lexer, StringLiterals) {
    LEXER_OPEN("src/tests/test_src/lexer/literals/string_literals.vc");

    Token stringLiterals[5];

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

    return true;
}

TEST(Lexer, IntegerLiterals) {
    LEXER_OPEN("src/tests/test_src/lexer/literals/integer_literals.vc");

    Token integerLiterals[2];

    //TEST_TOKEN_TYPE_ARRAY(integerLiterals, expectedIntegerTypes, 2);
    //TEST_TOKEN_VALUE_ARRAY(integerLiterals, expectedIntegerValues, 2);

    lexer.nextToken(&integerLiterals[0]);
    TEST_ASSERT(integerLiterals[0].kind == TokenKind::IntegerLiteral);
    TEST_ASSERT(integerLiterals[0].string == "12345");

    lexer.nextToken(&integerLiterals[1]);
    TEST_ASSERT(integerLiterals[1].kind == TokenKind::IntegerLiteral);
    TEST_ASSERT(integerLiterals[1].string == "-12345");

    return true;
}

/*

TEST(Lexer, HexIntegerLiterals) {
    LEXER_OPEN("src/tests/test_src/lexer/literals/hex_integer_literals.vc");

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

    return true;
}

TEST(Lexer, BinaryIntegerLiterals) {
    LEXER_OPEN("src/tests/test_src/lexer/literals/binary_integer_literals.vc");

    Token binaryLiterals[2];

    lexer.nextToken(&binaryLiterals[0]);
    TEST_ASSERT(binaryLiterals[0].kind == TokenKind::BinaryIntegerLiteral);
    TEST_ASSERT(binaryLiterals[0].string == "00001111");

    lexer.nextToken(&binaryLiterals[1]);
    TEST_ASSERT(binaryLiterals[1].kind == TokenKind::BinaryIntegerLiteral);
    TEST_ASSERT(binaryLiterals[1].string == "11111111");

    return true;
}
TEST(Lexer, OctalIntegerLiterals) {
    LEXER_OPEN("src/tests/test_src/lexer/literals/octal_integer_literals.vc");

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

    return true;
}
*/
TEST(Lexer, RealLiterals) {
    LEXER_OPEN("src/tests/test_src/lexer/literals/real_literals.vc");

    Token realLiterals[12];

    lexer.nextToken(&realLiterals[0]);
    TEST_ASSERT(realLiterals[0].kind == TokenKind::Real64Literal);
    TEST_ASSERT(realLiterals[0].string == "123.123");

    lexer.nextToken(&realLiterals[1]);
    TEST_ASSERT(realLiterals[1].kind == TokenKind::Real64Literal);
    TEST_ASSERT(realLiterals[1].string == "-123.123");

    lexer.nextToken(&realLiterals[2]);
    TEST_ASSERT(realLiterals[2].kind == TokenKind::Real32Literal);
    TEST_ASSERT(realLiterals[2].string == "0.0f");

    lexer.nextToken(&realLiterals[3]);
    TEST_ASSERT(realLiterals[3].kind == TokenKind::Real32Literal);
    TEST_ASSERT(realLiterals[3].string == "123.123f");

    lexer.nextToken(&realLiterals[4]);
    TEST_ASSERT(realLiterals[4].kind == TokenKind::Real32Literal);
    TEST_ASSERT(realLiterals[4].string == "123.f");

    lexer.nextToken(&realLiterals[5]);
    TEST_ASSERT(realLiterals[5].kind == TokenKind::Real32Literal);
    TEST_ASSERT(realLiterals[5].string == ".0f");

    lexer.nextToken(&realLiterals[6]);
    TEST_ASSERT(realLiterals[6].kind == TokenKind::Real32Literal);
    TEST_ASSERT(realLiterals[6].string == "-123.f");

    lexer.nextToken(&realLiterals[7]);
    TEST_ASSERT(realLiterals[7].kind == TokenKind::Real64Literal);
    TEST_ASSERT(realLiterals[7].string == "0.0");

    lexer.nextToken(&realLiterals[8]);
    TEST_ASSERT(realLiterals[8].kind == TokenKind::Real64Literal);
    TEST_ASSERT(realLiterals[8].string == "123.0d");

    lexer.nextToken(&realLiterals[9]);
    TEST_ASSERT(realLiterals[9].kind == TokenKind::Real64Literal);
    TEST_ASSERT(realLiterals[9].string == "-123.0d");

    lexer.nextToken(&realLiterals[10]);
    TEST_ASSERT(realLiterals[10].kind == TokenKind::Real64Literal);
    TEST_ASSERT(realLiterals[10].string == ".0d");

    lexer.nextToken(&realLiterals[11]);
    TEST_ASSERT(realLiterals[11].kind == TokenKind::Real64Literal);
    TEST_ASSERT(realLiterals[11].string == "-123.d");

    return true;
}