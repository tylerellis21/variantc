#include <vc/compiler/parser.h>

namespace vc {

bool Parser::parseDeclaration(Decl* parentDecl, DeclGroup* declGroup) {
    switch (current.kind) {

    case TokenKind::None: return true;

    case TokenKind::Enum: return parseEnumDecl(parentDecl, declGroup);
    case TokenKind::Package: return parsePackageDecl(parentDecl, declGroup);
    case TokenKind::Namespace: return parseNamespaceDecl(parentDecl, declGroup);
    case TokenKind::Using: return parseUsingDecl(parentDecl, declGroup);
    case TokenKind::Typedef: return parseTypedefDecl(parentDecl, declGroup);
    case TokenKind::Import: return parseImportDecl(parentDecl, declGroup);

    case TokenKind::Struct:
    case TokenKind::Union: return parseRecordDecl(parentDecl, declGroup);

    // Currently extern is only used to mark functions and variables from c
    case TokenKind::Extern:
        return parseFunctionDecl(parentDecl, declGroup);

    // case TokenKind::At: return parse_pp_decl(parentDecl, declGroup);

    // build a case for each TYPE_TOKEN.
    #define BUILTIN_KIND(NAME, TOKEN, SIZE) case TokenKind::##NAME:
    #include <vc/defs/builtin_kinds.inl>
    #undef BUILTIN_KIND
    // Fall through
    {
        if (!parseCompoundVarDecl(parentDecl, declGroup)) return false;
        return expectSemi();
    } break;

    // Check for a call expression
    case TokenKind::Identifier: {
        if (!parseCompoundVarDecl(parentDecl, declGroup)) return false;
        return expectSemi();
    } break;

    case TokenKind::Def: return parseFunctionDecl(parentDecl, declGroup);

    default:
        //utf8 str = token_symbol_or_string(current.kind);
        //report_error(lexer->fb, loc(), "unexpected token '%s' in top level declaration\n", str.buffer);
        return false;
    }
    return true;
}

bool parseUsing_decl(Decl* parentDecl, DeclGroup* declGroup);
bool parseTypedefDecl(Decl* parentDecl, DeclGroup* declGroup);
bool parseTemplateDecl(Decl* parentDecl, Decl** out);
bool parseImportDecl(Decl* parentDecl, DeclGroup* declGroup);
bool parseEnumDecl(Decl* parentDecl, DeclGroup* declGroup);
bool parseNamespaceDecl(Decl* parentDecl, DeclGroup* declGroup);
bool parseRecordDecl(Decl* parentDecl, DeclGroup* declGroup);
bool parseFunctionDecl(Decl* parentDecl, DeclGroup* declGroup);
bool parseFunctionArgDecl(Decl* parentDecl, FunctionArgDecl** out);
bool parseSingleVarDecl(Decl* parentDecl, VarDecl** out, Type* type = 0);
bool parseCompoundVarDecl(Decl* parentDecl, DeclGroup* declGroup, Type* type = 0);

} // namespace vc

