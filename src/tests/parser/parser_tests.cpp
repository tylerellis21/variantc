#include "../lexer_shared.h"
#include <vc/compiler/parser.h>

TEST(Parser, FullyQualifiedName) {
    LEXER_OPEN("src/tests/test_src/parser/fully-qualified-name.vc");
    Parser parser(&lexer);
    if (!parser.open()) {
        return false;
    }

    Name name;
    parser.parseName(&name, true);

    TEST_ASSERT(name.identifiers.size() == 4);
    TEST_ASSERT(name.identifiers.at(0).string == std::string("foo"));
    TEST_ASSERT(name.identifiers.at(1).string == std::string("bar"));
    TEST_ASSERT(name.identifiers.at(2).string == std::string("test"));
    TEST_ASSERT(name.identifiers.at(3).string == std::string("A"));

    return true;
}