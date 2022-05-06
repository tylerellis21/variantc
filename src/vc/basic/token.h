#ifndef VC_TOKEN_H_INCLUDE
#define VC_TOKEN_H_INCLUDE

#include <string>

#include <vc/basic/sourcelocation.h>

namespace vc {

enum TokenKind {
    Null = 0
};

struct Token {
    TokenKind kind;
    SourceLocation loc;
    std::string string;
};

}

#endif // VC_TOKEN_H_INCLUDE