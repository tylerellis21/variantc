#include <vc/compiler/lexer.h>

using namespace vc;

int main(int argc, char** args) {
    Lexer lexer;
    if (!lexer.open("src/tests/basic.vc")) {
        return -1;
    }

    Token token;
    lexer.nextToken(&token);


    //TODO: Run all tests.

    return 0;
}
