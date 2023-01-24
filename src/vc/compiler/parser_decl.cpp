#include <vc/compiler/parser.h>

namespace vc {

bool Parser::parseDeclaration(Decl* parentDecl, DeclGroup* declGroup) {
    switch (current.kind) {

    case TokenKind::None: return true;

    case TokenKind::Enum: return parseEnumDecl(parentDecl, declGroup);
    case TokenKind::Namespace: return parseNamespaceDecl(parentDecl, declGroup);
    case TokenKind::Using: return parseUsingDecl(parentDecl, declGroup);
    case TokenKind::Typedef: return parseTypedefDecl(parentDecl, declGroup);
    case TokenKind::Import: return parseImportDecl(parentDecl, declGroup);

    case TokenKind::Struct:
    case TokenKind::Union: return parseRecordDecl(parentDecl, declGroup);

    // Currently extern is only used to mark functions and variables from c
    case TokenKind::Extern: return parseFunctionDecl(parentDecl, declGroup);

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
        std::cout << "unexpected token in declaration: " << current << std::endl;
        return false;
    }
    return true;
}

bool Parser::parseUsingDecl(Decl* parentDecl, DeclGroup* declGroup) {
}

bool Parser::parseTypedefDecl(Decl* parentDecl, DeclGroup* declGroup) {
}

bool Parser::parseTemplateDecl(Decl* parentDecl, Decl** out) {
}

bool Parser::parseImportDecl(Decl* parentDecl, DeclGroup* declGroup) {
}

bool Parser::parseEnumDecl(Decl* parentDecl, DeclGroup* declGroup) {
}

bool Parser::parseNamespaceDecl(Decl* parentDecl, DeclGroup* declGroup) {
}

bool Parser::parseRecordDecl(Decl* parentDecl, DeclGroup* declGroup) {
}

bool Parser::parseFunctionDecl(Decl* parentDecl, DeclGroup* declGroup) {
}

bool Parser::parseFunctionArgDecl(Decl* parentDecl, FunctionArgDecl** out) {
}

bool Parser::parseSingleVarDecl(Decl* parentDecl, VarDecl** out, Type* type) {
}

bool Parser::parseCompoundVarDecl(Decl* parentDecl, DeclGroup* declGroup, Type* type) {
}

} // namespace vc

