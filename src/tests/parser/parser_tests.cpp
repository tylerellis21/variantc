#include "../lexer_shared.h"
#include <vc/compiler/parser.h>

#define PARSER_OPEN(PATH) \
    LEXER_OPEN(PATH); \
    Parser parser(&lexer); \
    if (!parser.open()) { \
        return false; \
    }

TEST(Parser, FullyQualifiedName) {

    PARSER_OPEN("src/tests/test_src/parser/fully-qualified-name.vc");

    Name name;
    parser.parseName(&name, true);

    TEST_ASSERT(name.identifiers.size() == 4);
    TEST_ASSERT(name.identifiers.at(0).string == std::string("foo"));
    TEST_ASSERT(name.identifiers.at(1).string == std::string("bar"));
    TEST_ASSERT(name.identifiers.at(2).string == std::string("test"));
    TEST_ASSERT(name.identifiers.at(3).string == std::string("A"));

    return true;
}

TEST(Parser, UsingDecl) {

    PARSER_OPEN("src/tests/test_src/parser/decl/using-decl.vc");

    DeclGroup* dg = new DeclGroup(0);

    TEST_ASSERT(parser.parseDecl(0, dg) == true);

    Decl* decl = dg->entries.front();

    TEST_ASSERT(decl != nullptr);
    TEST_ASSERT(decl->declKind == DeclKind::UsingDecl);

    return true;
}