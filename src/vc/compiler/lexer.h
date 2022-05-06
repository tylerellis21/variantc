#ifndef VC_LEXER_H_INCLUDE
#define VC_LEXER_H_INCLUDE

#include <vc/basic/token.h>

namespace vc {

struct FileBuffer;

struct Lexer {
    int offset;
    char prev, current, next;

    FileBuffer* fb;

    bool open(FileBuffer* fileBuffer);

    bool isMoreChars();

    char readChar();
    char peekChar();

    Token nextToken();
};

}

#endif // VC_LEXER_H_INCLUDE