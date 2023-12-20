#include <vc/val.h>
#include <vc/compiler.h>
#include <vc/basic/report.h>
#include <vc/ast/printer.h>

namespace t {
namespace vc {

bool Val::visit_ArrayType(ArrayType* array_type) {
    return true;
}

bool Val::visit_BasicType(BasicType* basic_type) {
    return true;
}

bool Val::visit_DeclRefType(DeclRefType* decl_ref_type) {

    Name* ref_name = decl_ref_type->name;
    Decl* ref_decl = 0;

    return true;
}

bool Val::visit_PointerType(PointerType* pointer_type) {
    return true;
}

bool Val::visit_TemplateType(TemplateType* template_type) {
    return true;
}

bool Val::visit_VarArgType(VarArgType* vararg_type) {
    return true;
}

} // namespace vc
} // namespace t
