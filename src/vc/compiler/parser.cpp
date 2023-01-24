#include <vc/compiler/parser.h>
#include <vc/compiler/lexer.h>

namespace vc {

Parser::Parser(Lexer* lexer) {
    this->lexer = lexer;
}

bool Parser::valid() {
    return lexer->isMoreChars() || current.kind != TokenKind::None;
}

bool Parser::open() {
    lexer->nextToken(&current);
    lexer->nextToken(&next);
    return true;
}

SourceLocation Parser::loc() {
    if (current.kind == TokenKind::None) {
        return SourceLocation::None;
    }
    return current.loc;
}

SourceLocation Parser::consume() {
    SourceLocation l = loc();

    prev = current;
    current = next;

    lexer->nextToken(&next);

    return l;
}

bool Parser::expect(TokenKind tokenKind) {
    if (current.kind != tokenKind) {
        std::cout << "expected token kind: " << tokenKind << " at: " << current << std::endl;
        return false;
    }
    return true;
}

bool Parser::expectConsume(TokenKind tokenKind) {
    if (expect(tokenKind)) {
        consume();
        return true;
    }
    return false;
}

bool Parser::expectSemi() {
    if (current.kind != TokenKind::Semi) {
        std::cout << "expected semicolon at: " << current << std::endl;
        return false;
    }
    consume();
    return true;
}

bool Parser::parseName(Name* name, bool fullyQualifiedName) {
    if (expect(TokenKind::Identifier) == false) return false;

    while (valid()) {
        if (current.kind != TokenKind::Identifier) {
            break;
        }

        name->identifiers.push_back(current);
        consume();

        if (current.kind == TokenKind::ColonColon && fullyQualifiedName) {
            consume();
        }
    }

    return true;
}

} // namespace vc