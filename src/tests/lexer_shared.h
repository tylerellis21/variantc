#ifndef LEXER_SHARED_H_INCLUDE
#define LEXER_SHARED_H_INCLUDE

#include <vc/compiler/lexer.h>

#include "unit_test.h"

using namespace vc;
using namespace cpptest;

#define LEXER_OPEN(filePath) \
    Lexer lexer; \
    if (!lexer.open(filePath)) { \
        return false; \
    }

#endif // LEXER_SHARED_H_INCLUDE