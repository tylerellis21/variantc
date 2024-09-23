#include <vc/parser.h>

namespace t {
namespace vc {

bool Parser::expect_kind(TokenKind kind) {
    if (current.kind != kind) {

        SourceLocation l = loc();
        if (current.kind == TokenKind::EndOfFile) {
            l = behind.loc;
        }

        utf8 str = token_symbol_or_string(current.kind);
        report_error(lexer->fb, l, "expected: %s got %s\n", token_str(kind).buffer, str.buffer);

        return false;
    }
    return true;
}

bool Parser::expect_consume(TokenKind kind) {
    if (expect_kind(kind)) {
        consume();
        return true;
    }
    return false;
}

bool Parser::open() {

    failed = false;

    // setup for proper parsing.
    lexer->next_token(&current);
    lexer->next_token(&ahead);

    return true;
}

SourceLocation Parser::consume() {
    SourceLocation l = loc();

    behind = current;
    current = ahead;

    lexer->next_token(&ahead);
    return l;
}

bool Parser::parse(Decl** result) {

    ModuleDecl* module = new ModuleDecl(0);

    while (true) {

        if (!parse_top_level_decl(module, module->dg))
            return false;

        if (current.kind == TokenKind::EndOfFile)
            break;

        // we check the parse valid case at the end so we are able to parse a token if it's at the end of a file.
        if (!valid()) break;
    }

    *result = module;

    return true;
}

bool Parser::parse_top_level_decl(Decl* parent, DeclGroup* dg) {

    switch (current.kind) {

    case TokenKind::EndOfFile: return true;
    case TokenKind::Enum: return parse_enum_decl(parent, dg);
    case TokenKind::Package: return parse_package_decl(parent, dg);
    case TokenKind::Namespace: return parse_namespace_decl(parent, dg);
    case TokenKind::Using: return parse_using_decl(parent, dg);
    case TokenKind::Typedef: return parse_typedef_decl(parent, dg);
    case TokenKind::Import: return parse_import_decl(parent, dg);

    case TokenKind::Struct:
    case TokenKind::Union: return parse_record_decl(parent, dg);

    // Currently extern is only used to mark functions and variables from c
    case TokenKind::Extern:
        return parse_function_decl(parent, dg);

    case TokenKind::At: return parse_pp_decl(parent, dg);

    // build a case for each TYPE_TOKEN.
    #define TYPE_TOKEN(TOKEN) case TokenKind::TOKEN:
    TYPE_TOKENS
    #undef TYPE_TOKEN
    // Fall through
    {
        if (!parse_compound_var_decl(parent, dg)) return false;
        return expect_semi();
    } break;

    // Check for a call expression
    case TokenKind::Identifier: {
        if (!parse_compound_var_decl(parent, dg)) return false;
        return expect_semi();
    } break;

    case TokenKind::Def: return parse_function_decl(parent, dg);

    default:
        utf8 str = token_symbol_or_string(current.kind);
        report_error(lexer->fb, loc(), "unexpected token '%s' in top level declaration\n", str.buffer);
        return false;
    }
}

} // namespace vc
} // namespace t
