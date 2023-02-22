#include <vc/compiler/parser.h>

#include <vc/ast/stmt.h>
#include <vc/ast/expr.h>

namespace vc {

bool Parser::parseDecl(Decl* parentDecl, DeclGroup* declGroup) {
    switch (current.kind) {

    case TokenKind::None: return true;

    case TokenKind::Enum: return parseEnumDecl(parentDecl, declGroup);
    case TokenKind::Namespace: return parseNamespaceDecl(parentDecl, declGroup);
    case TokenKind::Using: return parseUsingDecl(parentDecl, declGroup);
    case TokenKind::Typedef: return parseTypedefDecl(parentDecl, declGroup);
    case TokenKind::Import: return parseImportDecl(parentDecl, declGroup);

    case TokenKind::Struct:
    case TokenKind::Union:
    case TokenKind::Interface: return parseRecordDecl(parentDecl, declGroup);

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
    SourceLocation startLoc = loc();

    if (!expectConsume(TokenKind::Using)) return false;

    Name name;
    if (!parseName(&name, true)) return false;

    if (!expectSemi()) return false;

    UsingDecl* decl = new UsingDecl(parentDecl, startLoc, name);
    declGroup->entries.push_back(decl);
    return true;
}

bool Parser::parseTypedefDecl(Decl* parentDecl, DeclGroup* declGroup) {
    SourceLocation loc = consume();

    Type* type = 0;
    if (!parseType(&type)) return false;

    Name name;
    if (!parseName(&name, false)) return false;

    if (!expectSemi()) return false;

    TypedefDecl* typedefDecl = new TypedefDecl(parentDecl, loc, name, type);

    declGroup->add(typedefDecl);

    return true;
}

/*

bool Parser::parseTemplateDecl(Decl* parentDecl, DeclGroup* declGroup) {
    TemplateDecl* templateDecl = 0;
    bool result = parseTemplateDecl(parentDecl, declGroup, &templateDecl);
    if (result) {
        declGroup->add(templateDecl);
    }
    return result;
}

bool Parser::parseTemplateDecl(Decl* parentDecl, DeclGroup* declGroup, TemplateDecl** templateDecl) {
    SourceLocation sloc = loc();
    if (!expectConsume(TokenKind::Less)) return false;

    DeclGroup* templateDeclGroup = new DeclGroup(declGroup);

    *templateDecl = new TemplateDecl(parentDecl, sloc, templateDeclGroup);

    while (valid()) {

        Name name;
        if (!parseName(&name, false)) return false;

        TemplateNameDecl* templateNameDecl = new TemplateNameDecl(*templateDecl, sloc, name);

        templateDeclGroup->add(templateNameDecl);

        if (current.kind == TokenKind::Comma) {
            consume();
            continue;
        }
        else break;
    }

    if (!expectConsume(TokenKind::Greater)) return false;

    return true;
}

*/

bool Parser::parseImportDecl(Decl* parentDecl, DeclGroup* declGroup) {
    SourceLocation loc = consume();

    Name name;
    if (!parseName(&name, true)) return false;
    if (!expectSemi()) return false;

    ImportDecl* importDecl = new ImportDecl(parentDecl, loc, name);

    declGroup->add(importDecl);

    return true;
}

bool Parser::parseEnumDecl(Decl* parentDecl, DeclGroup* declGroup) {
    SourceLocation sloc = consume();

    Name name;
    if (!parseName(&name, false)) return false;

    // Check for a typed enum
    Type* type = 0;
    if (current.kind == TokenKind::Colon) {
        consume();
        if (!parseType(&type)) return false;
    }

    DeclGroup* enumDeclGroup = new DeclGroup(declGroup);
    EnumDecl* enumDecl = new EnumDecl(
        parentDecl,
        sloc,
        SourceRange::None,
        name,
        enumDeclGroup,
        type
    );

    SourceRange sourceRange;
    sourceRange.begin = loc();

    if (!expectConsume(TokenKind::LBrace)) return false;

    while(valid()) {
        if (current.kind == TokenKind::RBrace) break;
        else {
            SourceLocation enumConstLoc = loc();

            Name enumConstName;

            if (!parseName(&enumConstName, false)) return false;

            Expr* enumValueExpr = 0;
            if (current.kind == TokenKind::Equal) {
                consume();
                enumValueExpr = parseCastExpr(0);
            }

            EnumConstDecl* enumConstDecl = new EnumConstDecl(
                enumDecl,
                enumConstLoc,
                enumConstName,
                enumValueExpr
            );

            enumDeclGroup->add(enumConstDecl);

            if (current.kind == TokenKind::Comma) {
                consume();
                continue;
            }
            else break;
        }
    }

    sourceRange.end = loc();
    if (!expectConsume(TokenKind::RBrace)) return false;

    enumDecl->sourceRange = sourceRange;

    declGroup->add(enumDecl);
    return true;
}

bool Parser::parseNamespaceDecl(Decl* parentDecl, DeclGroup* declGroup) {
    SourceLocation keywordLoc = loc();
    if (!expectConsume(TokenKind::Namespace))
        return false;

    Name name;
    if (!parseName(&name, true)) return false;

    SourceRange sourceRange;
    sourceRange.begin = loc();

    if (!expectConsume(TokenKind::LBrace)) return false;

    // create a new scope for the namespace
    DeclGroup* namespaceDeclGroup = new DeclGroup(declGroup);

    NamespaceDecl* namespaceDecl = new NamespaceDecl(
        parentDecl,
        SourceRange::None,
        name,
        namespaceDeclGroup
    );

    while (valid()) {
        if (current.kind == TokenKind::RBrace) {
            break;
        }
        // use the declarations new scope for sub declarations
        if (!parseDecl(namespaceDecl, namespaceDecl->declGroup)) return false;
    }

    sourceRange.end = loc();
    if (!expectConsume(TokenKind::RBrace)) return false;

    namespaceDecl->sourceRange = sourceRange;

    declGroup->add(namespaceDecl);
    return true;
}

bool Parser::parseRecordDecl(Decl* parentDecl, DeclGroup* declGroup) {
    Name recordName;
    //TemplateDecl* recordTemplateDecl = 0;

    RecordKind recordKind;

    switch (current.kind) {
    default: return false;
    case TokenKind::Union: recordKind = RecordKind::UnionKind; break;
    case TokenKind::Struct: recordKind = RecordKind::StructKind; break;
    }

    // Mark the location of the keyword
    SourceLocation keywordLoc = consume();

    if (current.kind == TokenKind::Identifier) {
        if (!parseName(&recordName, false)) return false;
    }

    DeclGroup* recordDeclGroup = new DeclGroup(declGroup);
    RecordDecl* recordDecl = new RecordDecl(
        parentDecl,
        keywordLoc,
        recordKind,
        recordName,
        declGroup
    );

    /*
    // We have a template declaration
    if (current.kind == TokenKind::At) {
        if (!parseTemplateDecl(recordDecl, declGroup, &recordTemplateDecl)) return false;
    }
    */

    SourceRange sourceRange;
    sourceRange.begin = loc();

    if (!expectConsume(TokenKind::LBrace)) return false;

    while (valid()) {
        if (current.kind == TokenKind::RBrace) break;
        if (!parseDecl(recordDecl, recordDeclGroup)) return false;
    }

    sourceRange.end = loc();
    if (!expectConsume(TokenKind::RBrace)) return false;

    recordDecl->sourceRange = sourceRange;
    // recordDecl->templateDecl = recordTemplateDecl;

    declGroup->add(recordDecl);
    return true;
}

bool Parser::parseFunctionDecl(Decl* parentDecl, DeclGroup* declGroup) {
    SourceLocation keywordLoc = loc();

    // Do we need to generate a Type for this function?
    bool isExtern = false;
    bool isProto = false;
    bool isInline = false;

    Name functionName;
    Type* functionReturnType = 0;
    Stmt* functionBodyStmt = 0;
    // TemplateDecl* functionTemplateDecl = 0;

    std::vector<FunctionArgDecl*> functionArgs;

    if (current.kind == TokenKind::Extern) {
        isExtern = true;
        consume();
    }
    else if (current.kind == TokenKind::Inline) {
        isInline = true;
        consume();
    }

    if (!expectConsume(TokenKind::Def)) return false;

    // If we are being called from a template the name was already pre parsed
    if (functionName.identifiers.size() == 0)
        if (!parseName(&functionName, false)) return false;

    FunctionDecl* functionDecl = new FunctionDecl(
        parentDecl,
        keywordLoc,
        functionName,
        functionArgs,
        functionReturnType,
        functionBodyStmt
    );

    /*
    // Check for template declaration
    if (current.kind == TokenKind::Less) {
        if (!parseTemplateDecl(functionDecl, declGroup, &functionTemplateDecl)) return false;
    }
    */

    if (!expectConsume(TokenKind::LParen)) return false;

    while (valid()) {
        if (current.kind == TokenKind::RParen) break;

        FunctionArgDecl* functionArgDecl = 0;
        if (!parseFunctionArgDecl(functionDecl, &functionArgDecl)) return false;

        functionArgs.push_back(functionArgDecl);

        if (current.kind == TokenKind::Comma) consume();
        else break;
    }

    if (!expectConsume(TokenKind::RParen)) return false;

    SourceLocation type_start = loc();
    if (!parseType(&functionReturnType)) {
        //report_error(lexer->fb, type_start, "function type specifier is missing!\n");
        return false;
    }

    if (current.kind == TokenKind::LBrace) {
        if (!parseCompoundStmt(0, &functionBodyStmt)) return false;
    }
    else {
        isProto = true;
        if (expectSemi()) return false;
    }

    functionDecl->isPrototype = isProto;
    functionDecl->isInline = isInline;
    functionDecl->isExtern = isExtern;
    functionDecl->args = functionArgs;
    functionDecl->body = functionBodyStmt;
    functionDecl->returnType = functionReturnType;

    declGroup->add(functionDecl);

    return true;
}

bool Parser::parseFunctionArgDecl(Decl* parentDecl, FunctionArgDecl** out) {
    SourceLocation sloc = loc();
    bool isVarArg = false;
    VarDecl* varDecl = 0;

    if (current.kind == TokenKind::Ellipsis) {
        isVarArg = true;
        consume();
    }
    else {
        if (!parseSingleVarDecl(parentDecl, &varDecl, 0)) return false;
    }

    *out = new FunctionArgDecl(parentDecl, sloc, varDecl, isVarArg);
    return true;
}

bool Parser::parseSingleVarDecl(Decl* parentDecl, VarDecl** out, Type* type) {
    SourceLocation sloc = loc();

    Name name;
    Expr* assignment = 0;
    Expr* bitsizeExpr = 0;

    if (!type) if (!parseType(&type)) return false;

    if (!parseName(&name, false)) return false;

    if (current.kind == TokenKind::Colon) {
        consume();
        bitsizeExpr = parseIntegerLiteralExpr(0);
    }

    if (current.kind == TokenKind::Equal)
        assignment = parseAssignmentExpr(0);

    VarDecl* varDecl = new VarDecl(
        parentDecl,
        sloc,
        type,
        name,
        assignment
    );

    varDecl->bitsize = bitsizeExpr;

    *out = varDecl;
    return true;
}

bool Parser::parseCompoundVarDecl(Decl* parentDecl, DeclGroup* declGroup, Type* type) {
    while (valid()) {

        // type will get set on the first call only! when: (type == 0)
        // then be used for all following variable declarations
        VarDecl* varDecl = 0;
        if (!parseSingleVarDecl(parentDecl, &varDecl, type)) return false;

        declGroup->add(varDecl);

        if (current.kind == TokenKind::Comma) {
            consume();
            continue;
        }
        else
            break;
    }

    return true;
}

} // namespace vc

