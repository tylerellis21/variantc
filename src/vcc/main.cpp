#include <string>
#include <vector>

#include <vc/compiler/lexer.h>
#include <vc/basic/filebuffer.h>

// Let's work backwards. Let's build the ast structure then attempt to build the ir code generation before we 
// build out the entire lexer/parser/compiler

int main(int argc, char** args) {

    char* input = args[1];

    vc::FileBuffer fb;
    if (fb.load(input) == false) {
        return -1;
    }
    
    return 0;
}