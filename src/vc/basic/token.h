#ifndef VC_TOKEN_H_INCLUDE
#define VC_TOKEN_H_INCLUDE

#include <string>
#include <iostream>

#include <vc/basic/sourcelocation.h>
#include <vc/basic/tokenkind.h>

namespace vc {

struct Token {
    TokenKind kind;
    SourceLocation loc;
    std::string string;
};

std::ostream& operator <<(std::ostream& out, const Token& token);

}

#endif // VC_TOKEN_H_INCLUDE
