#include "../lexer_shared.h"

TEST(Lexer, BuiltinIntegerTypes) {
    LEXER_OPEN("src/tests/test_src/lexer/types/builtin_integer_types.vc");

    return true;
}

TEST(Lexer, BuiltinUnsignedIntegerTypes) {
    LEXER_OPEN("src/tests/test_src/lexer/types/builtin_unsigned_integer_types.vc");

    return true;
}

TEST(Lexer, BuiltinFloatingPointTypes) {
    LEXER_OPEN("src/tests/test_src/lexer/types/builtin_floating_point_types.vc");

    return true;
}