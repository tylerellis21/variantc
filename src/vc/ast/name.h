#ifndef VC_NAME_H_INCLUDE
#define VC_NAME_H_INCLUDE

#include <vector>

#include <vc/types.h>
#include <vc/basic/sourcelocation.h>
#include <vc/basic/token.h>

namespace vc {

struct Name {
    std::vector<Token> identifiers;

    Name(std::vector<Token> identifiers) :
        identifiers(identifiers)
    { }

    Name() :
        identifiers(std::vector<Token>())
    { }
};


std::ostream& operator <<(std::ostream& out, const Name& name);

}

#endif // VC_NAME_H_INCLUDE
