#include <vc/val.h>
#include <vc/compiler.h>
#include <vc/basic/report.h>

#include <t/struct/map.h>

namespace t {
namespace vc {

bool Val::visit_Decl(Decl* decl) {
    return true;
}

bool Val::visit_EnumDecl(EnumDecl* enum_decl) {
/*
    // If we find a duplicate return false.
    if (local_scope_duplicate_check(enum_decl)) return false;

    // If we find a duplicate return false.
    if (global_typename_check(enum_decl)) return false;
*/
    return true;
}

bool Val::visit_EnumConstDecl(EnumConstDecl* enum_const_decl) {
    return true;
}

bool Val::visit_ModuleDecl(ModuleDecl* module_decl) {
    return true;
}

bool Val::visit_FunctionDecl(FunctionDecl* function_decl) {
/*
    // If we find a duplicate return false.
    if (local_scope_duplicate_check(function_decl)) return false;

    // If we find a duplicate return false.
    if (global_typename_check(function_decl)) return false;
*/
    return true;
}

bool Val::visit_FunctionArgDecl(FunctionArgDecl* function_arg_decl) {
    return true;
}

bool Val::visit_NamespaceDecl(NamespaceDecl* namespace_decl) {
    return true;
}

bool Val::visit_PackageDecl(PackageDecl* package_decl) {
    return true;
}

bool Val::visit_RecordDecl(RecordDecl* record_decl) {
/*
    // If we find a duplicate return false.
    if (local_scope_duplicate_check(record_decl)) return false;

    // If we find a duplicate return false.
    if (global_typename_check(record_decl)) return false;

    // Search for shadowed declarations in the higher level scopes.
*/
    return true;
}

bool Val::visit_TemplateDecl(TemplateDecl* template_decl) {
    return true;
}

bool Val::visit_TemplateNameDecl(TemplateNameDecl* template_name_decl) {
    return true;
}

bool Val::visit_TypedefDecl(TypedefDecl* typedef_decl) {
    return true;
}

bool Val::visit_UsingDecl(UsingDecl* using_decl) {
    return true;
}

bool Val::visit_VarDecl(VarDecl* var_decl) {

    // If there is not parent we must be a declaration inside of a 
    // declstmt, so we just reference the top of the stack. 
    if (!var_decl->parent) {
        // Sub 2 since the var decl is also pushed on the stack.
        var_decl->parent = *(decl_stack.data + decl_stack.offset - 2);
    }
    Decl* scope = find_decl_scope(var_decl->parent);

/*
    
    // If we find a duplicate return false.
    // This check only works on global variables or variables inside a record.
    if (local_scope_duplicate_check(var_decl)) return false;

    // Only check the typename if we are not in a function.
    if (var_decl->parent->kind != DeclKind::FunctionDecl)
        if (global_typename_check(var_decl)) return false;
*/
    return true;
}

bool Val::visit_ImportDecl(ImportDecl* import_decl) {
    return true;
}

bool Val::visit_PPIfDecl(PPIfDecl* pp_if_decl) {
    return true;
}

bool Val::visit_PPDefDecl(PPDefDecl* pp_def_decl) {
    return true;
}

bool Val::visit_PPUndefDecl(PPUndefDecl* pp_undef_decl) {
    return true;
}

} // namespace vc
} // namespace t
