#ifndef VC_TOKEN_MAP_H_INCLUDE
#define VC_TOKEN_MAP_H_INCLUDE

#include <vc/basic/token.h>
#include <map>

namespace vc {

typedef std::map<std::string, vc::TokenKind> TokenMap;

extern const TokenMap tokenMap;

}

#endif // VC_TOKEN_MAP_H_INCLUDE
