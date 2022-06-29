#ifndef VC_LEXER_H_INCLUDE
#define VC_LEXER_H_INCLUDE

#include <vc/basic/tokenmap.h>
#include <vc/basic/sourcelocation.h>
#include <vc/basic/filebuffer.h>
#include <sstream>
#include <map>

namespace vc {


struct FileBuffer;

struct Lexer {
    int offset;
    char prev, current, next;
    SourceLocation sourceLocation;
    SourceLocation tokenLocation;

    FileBuffer fileBuffer;

    // used to build token strings.
    std::stringstream sstream;

    TokenMap tokenMap;

    Lexer(TokenMap tokenMap) :
        tokenMap(tokenMap)
    { }

    Lexer() :
        tokenMap(vc::tokenMap)
    { }

    bool open(std::string filePath);

    bool isMoreChars();

    void nextChar();
    
    void nextToken(Token* token);

    // Append the current char to the string stream
    void append();

    // Append the current char to the string stream
    // and the advance to the next char
    void appendConsume();

    // Take the string stream and construct a token of the given time.
    // Resets the string stream after storing the string in the token.
    void constructToken(Token* token, TokenKind kind);

    void lexNumeric(Token* token);
    void lexWord(Token* token);
    void lexOperator(Token* token);
    void lexEscapeSequence(Token* token);
    void lexString(Token* token);
    void lexCharacter(Token* token);
    void lexSingleLineComment();
    void lexMultiLineComment();
};

} // namespace vc

#endif // VC_LEXER_H_INCLUDE
