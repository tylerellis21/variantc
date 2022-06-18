#ifndef VC_LEXER_H_INCLUDE
#define VC_LEXER_H_INCLUDE

#include <vc/basic/token.h>
#include <vc/basic/sourcelocation.h>
#include <vc/basic/filebuffer.h>
#include <sstream>
#include <map>

namespace vc {

typedef std::map<std::string, vc::TokenKind> TokenMap;

struct FileBuffer;

struct Lexer {
    int offset;
    char prev, current, next;
    SourceLocation sourceLocation;

    FileBuffer fileBuffer;

    // used to build token strings.
    std::stringstream sstream;

    TokenMap tokenMap;

    Lexer(TokenMap tokenMap) :
        tokenMap(tokenMap)
    { }

    bool open(std::string filePath);

    bool isMoreChars();

    void nextChar();

    Token lexToken();
};

} // namespace vc

#endif // VC_LEXER_H_INCLUDE
