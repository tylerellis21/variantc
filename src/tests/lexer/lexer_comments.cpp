#include "../lexer_shared.h"

TEST(Lexer, Comments) {
    LEXER_OPEN("src/tests/test-src/lexer/comments.vc");

    Token token;
    lexer.nextToken(&token);

    TEST_ASSERT(token.kind == TokenKind::Null);
    TEST_ASSERT(lexer.isMoreChars() == false);

    return true;
}