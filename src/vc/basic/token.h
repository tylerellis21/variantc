#ifndef VC_TOKEN_H_INCLUDE
#define VC_TOKEN_H_INCLUDE

#include <string>

#include <vc/basic/sourcelocation.h>
#include <vc/basic/tokenkind.h>

namespace vc {

struct Token {
    TokenKind kind;
    SourceLocation loc;
    std::string string;
};

}

#endif // VC_TOKEN_H_INCLUDE
