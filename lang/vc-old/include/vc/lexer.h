#ifndef LEXER_H_INCLUDE
#define LEXER_H_INCLUDE

#include <t/core/string.h>
#include <t/core/stringbuilder.h>

#include <t/struct/list.h>
#include <t/struct/stack.h>

#include <vc/basic/file_buffer.h>
#include <vc/basic/source_location.h>
#include <vc/basic/token.h>
namespace t {
namespace vc {

struct InputFile;

struct Lexer {

    char ahead;
    char behind;
    char current;

    u64 offset;

    FileBuffer* fb;

    SourceLocation src_loc;
    SourceLocation tok_loc;
    StringBuilder<u8> tok_buffer;
    Stack<utf8> tok_stack;

    inline Lexer(FileBuffer* file_buffer) :
        fb(file_buffer),
        tok_buffer(100) {
    }

    inline void free() {
        tok_buffer.buffer.free();
        tok_stack.free();
    }

    /// \brief Setup the lexer for the given file.
    bool open();

    /// \brief This should be true until all characters have been advanced over.
    bool has_chars();

    bool has_tokens();

    void next_char();

    void next_token(Token* token);

    void append();
    void append_consume();

    void construct_token(Token* token, TokenKind kind);

    void lex_numeric(Token* token);
    void lex_word(Token* token);
    void lex_operator(Token* token);
    void lex_character_escape(Token* token);
    void lex_string(Token* token);
    void lex_character(Token* token);
    void lex_single_line_comment();
    void lex_multi_line_comment();
};

/// \brief Check if a character is considered to be whitespace.
bool is_whitespace(char ch);

} // namespace vc
} // namespace t

#endif // LEXER_H_INCLUDE
