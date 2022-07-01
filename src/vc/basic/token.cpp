#include <vc/basic/token.h>

namespace vc {

std::string toString(TokenKind tokenKind) {
    switch (tokenKind) {
        case TokenKind::Null: return "Null";

        case TokenKind::BooleanLiteral: return "BooleanLiteral";
    
        default: 
            return "";
    }
}

}