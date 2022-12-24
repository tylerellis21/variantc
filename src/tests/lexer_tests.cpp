#include <chrono>
#include <iostream>

#include "lexer_shared.h"


//TODO(@Tyler): Once we have string.join working replace theses full paths with a constant string base path of sorts.
// TODO(@Tyler): Make some helper functions to clean this up
// eg: TEST_TOKEN_KIND(TOKEN, EXPECTED_KIND)
// eg: TEST_TOKEN_VALUE(TOKEN, EXPECTED_VALUE)

// eg: TEST_TOKEN_KIND_ARRAY(TOKEN, EXPECTED_KIND_ARRAY, EXPECTED_KIND_ARRAY_LENGTH)
// eg: TEST_TOKEN_VALUE_ARRAY(TOKEN, EXPECTED_KIND)



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
    Numeric Literals
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