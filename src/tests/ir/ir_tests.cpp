#include <iostream>

#include "../lexer_shared.h"

#include <vc/ast/decl.h>
#include <vc/ast/declgroup.h>
#include <vc/ast/expr.h>
#include <vc/ast/name.h>
#include <vc/ast/stmt.h>
#include <vc/ast/type.h>

TEST(IRGen, Keywords) {
    DeclGroup* modDg = new DeclGroup(0);
    ModuleDecl* mod = new ModuleDecl(0, SourceLocation::None, modDg);
    return true;
}