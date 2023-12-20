#include <vc/ast/decl.h>

namespace t {
namespace vc {

Name* Decl::name() {
    switch (kind) {
    default:
    case DeclKind::Empty: return 0;
    case DeclKind::EnumConstDecl: return static_cast<EnumConstDecl*>(this)->name;
    case DeclKind::EnumDecl: return static_cast<EnumDecl*>(this)->name;
    case DeclKind::FunctionArgDecl: return static_cast<FunctionArgDecl*>(this)->name();
    case DeclKind::FunctionDecl: return static_cast<FunctionDecl*>(this)->name;
    case DeclKind::ImportDecl: return static_cast<ImportDecl*>(this)->name;
    case DeclKind::NamespaceDecl: return static_cast<NamespaceDecl*>(this)->name;
    case DeclKind::PackageDecl: return static_cast<PackageDecl*>(this)->name;
    case DeclKind::RecordDecl: return static_cast<RecordDecl*>(this)->name;

    // TODO: HMM
    case DeclKind::TemplateDecl: return 0;
    case DeclKind::TemplateNameDecl: return static_cast<TemplateNameDecl*>(this)->name;

    case DeclKind::TypedefDecl: return static_cast<TypedefDecl*>(this)->name;
    case DeclKind::UsingDecl: return static_cast<UsingDecl*>(this)->name;
    case DeclKind::VarDecl: return static_cast<VarDecl*>(this)->name;
    } // switch (kind)

    return 0;
}

Name* Decl::full_name() {
    switch (kind) {

    default: return name();

    case DeclKind::Empty: return 0;
    case DeclKind::EnumConstDecl: return static_cast<EnumConstDecl*>(this)->full_name;
    case DeclKind::EnumDecl: return static_cast<EnumDecl*>(this)->full_name;
    case DeclKind::FunctionArgDecl: return static_cast<FunctionArgDecl*>(this)->full_name();
    case DeclKind::FunctionDecl: return static_cast<FunctionDecl*>(this)->full_name;
    case DeclKind::NamespaceDecl: return static_cast<NamespaceDecl*>(this)->full_name;
    case DeclKind::RecordDecl: return static_cast<RecordDecl*>(this)->full_name;

    // TODO: HMM
    case DeclKind::TemplateDecl: return 0;
    case DeclKind::TemplateNameDecl: return static_cast<TemplateNameDecl*>(this)->full_name;

    case DeclKind::VarDecl: return static_cast<VarDecl*>(this)->full_name;
    } // switch (kind)


    return 0;
}

bool decl_compare(Decl* lhs, Decl* rhs) {

    // If we have the same pointer well... we have the same declaration....
    if (lhs == rhs) return true;

    // If they aren't the same kind well yeah....
    if (lhs->kind != rhs->kind) return false;

    switch (lhs->kind) {

    default:
    case DeclKind::Empty: return false;

    case DeclKind::FunctionArgDecl: {
        return decl_compare(((FunctionArgDecl*)lhs)->var_decl, rhs);
    } break;

    case DeclKind::FunctionDecl: {

        FunctionDecl* larg = (FunctionDecl*)lhs;
        FunctionDecl* rarg = (FunctionDecl*)rhs;

        if (!name_compare(
                    larg->name,
                    rarg->name)) return false;

        u64 arg_count = larg->args.count;

        if (larg->args.count != rarg->args.count) return false;

        for (u64 i = 0; i < arg_count; i++) {
            if (!decl_compare(
                        larg->args[i],
                        rarg->args[i])) return false;
        }

        return true;
    }

    case DeclKind::ModuleDecl: {
    } break;

    case DeclKind::NamespaceDecl: {
        NamespaceDecl* larg = (NamespaceDecl*)lhs;
        NamespaceDecl* rarg = (NamespaceDecl*)rhs;

        return name_compare(
                    larg->name,
                    rarg->name);
    }

    case DeclKind::PackageDecl: {
        PackageDecl* larg = (PackageDecl*)lhs;
        PackageDecl* rarg = (PackageDecl*)rhs;

        return name_compare(
                    larg->name,
                    rarg->name);
    }

    case DeclKind::RecordDecl: {
        RecordDecl* larg = (RecordDecl*)lhs;
        RecordDecl* rarg = (RecordDecl*)rhs;

        if (larg->record_kind != rarg->record_kind) return false;

        return name_compare(
                    larg->name,
                    rarg->name);
    }

    case DeclKind::UsingDecl: {

        UsingDecl* larg = (UsingDecl*)lhs;
        UsingDecl* rarg = (UsingDecl*)rhs;

        return name_compare(
                    larg->name,
                    rarg->name);
    }

    case DeclKind::VarDecl: {

        VarDecl* larg = (VarDecl*)lhs;
        VarDecl* rarg = (VarDecl*)rhs;

        return name_compare(
                    larg->name,
                    rarg->name);
    }

    case DeclKind::ImportDecl: {

        ImportDecl* larg = (ImportDecl*)lhs;
        ImportDecl* rarg = (ImportDecl*)rhs;

        return name_compare(larg->name, rarg->name);
    }

    } // switch (decl->kind)

    return false;
}

} // namespace vc
} // namespace t
