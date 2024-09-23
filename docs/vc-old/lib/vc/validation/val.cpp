#include <vc/val.h>
#include <vc/compiler.h>
#include <vc/basic/report.h>
#include <t/math/math.h>

namespace t {
namespace vc {

void Val::duplicate_declaration_found(Decl* a, Decl* b) {

    /*
sample.cpp:4:8: error: redefinition of 'Foo'
struct Foo { };
       ^
sample.cpp:3:8: note: previous definition is here
struct Foo { };
       ^
    */
    report_location(module->fb, a->loc);
    printf("redefinition of '%s'\n", (char*)name_str(a->name(), ' ').buffer);
    report_buffer_line(module->fb, a->loc);

    report_location(module->fb, b->loc);
    printf("previous definition is here '%s'\n", (char*)name_str(b->name(), ' ').buffer);
    report_buffer_line(module->fb, b->loc);
}

bool Val::local_scope_duplicate_check(Decl* decl) {

    Name* decl_name = decl->name();
    Decl* decl_scope = find_decl_scope(decl);

    // Search for duplicate declarations in the local scope.
    Decl* result = search_decl_scope(decl_name, decl_scope, decl);
    if (result) {
        duplicate_declaration_found(decl, result);
        return true;
    }

    return false;
}

bool Val::global_typename_check(Decl* decl) {

    Name* decl_full_name = decl->full_name();

    Decl* result = 0;
    if (local_type_map.search(*decl_full_name, &result)) {
        duplicate_declaration_found(decl, result);
        return true;
    }
    else {
        local_type_map.set(*decl_full_name, decl);
    }

    return false;
}

Decl* Val::find_decl_scope(Decl* decl) {

    if (!decl) return 0;

    switch(decl->kind) {

    default:
        t_assert(!"declaration has no scope!");
        break;

    case DeclKind::RecordDecl: 
    case DeclKind::VarDecl: 
        return find_decl_scope(decl->parent);

    case DeclKind::EnumDecl:
    case DeclKind::ModuleDecl: 
    case DeclKind::NamespaceDecl:
    case DeclKind::FunctionDecl: 
        return decl;

    } // switch (decl->parent)
    return 0;
}

Decl* Val::search_decl_scope(Name* name, Decl* scope, Decl* exclude) {
    
    if (!scope) return 0;

    switch (scope->kind) {

    default:
        t_assert(!"declaration is not a scope!");
        break;

    case DeclKind::EnumDecl: {
        EnumDecl* enum_decl = static_cast<EnumDecl*>(scope);
        return search_decl_scope_dg(name, enum_decl->dg, exclude);
    } break;

    case DeclKind::ModuleDecl: {
        ModuleDecl* module_decl = static_cast<ModuleDecl*>(scope);
        return search_decl_scope_dg(name, module_decl->dg, exclude);
    } break;

    case DeclKind::NamespaceDecl: {
        NamespaceDecl* namespace_decl = static_cast<NamespaceDecl*>(scope);
        return search_decl_scope_dg(name, namespace_decl->dg, exclude);
    } break;

    case DeclKind::RecordDecl: {
        RecordDecl* record_decl = static_cast<RecordDecl*>(scope);
        return search_decl_scope_dg(name, record_decl->dg, exclude);
    } break;

    case DeclKind::FunctionDecl: {
        //FunctionDecl* function_decl = static_cast<FunctionDecl*>(scope);
        //return search_decl_scope(function_decl->body, exclude);
    } break;


    } // switch (scope->kind)

    return 0;
}

Decl* Val::search_decl_scope_dg(Name* name, DeclGroup* dg, Decl* exclude) {
    for (Decl* decl : *dg) {
        if (*decl->name() == *name && decl != exclude) return decl;
    }
    return 0;
}

i64 Val::evaluate_type_size(Type* type) {
    switch (type->kind) {
        default: return 0;

        case TypeKind::ArrayType: {
            ArrayType* array_type = static_cast<ArrayType*>(type);

            // Figure out the size of one single element
            i64 array_type_size = evaluate_type_size(array_type->type);

            // Scale that size based on the length 
            // of the array to get the total number of bytes.
            return array_type_size * array_type->length;
        } 

        // Easy case, simply return the builtin size.
        case TypeKind::BasicType: {
            BasicType* basic_type = static_cast<BasicType*>(type);
            return basic_kind_size(basic_type->basic_kind);
        } 

        case TypeKind::DeclRefType: {
            DeclRefType* decl_ref_type = static_cast<DeclRefType*>(type);
            Decl* ref = decl_ref_type->decl;
            return ref != 0;
        } break;

        case TypeKind::PointerType: {
            //flags->
            // TODO(@Tyler): Current flags is passed into the Val object.
            // IDK. MEH.
            return 8;
        } 

        case TypeKind::TemplateType: {
            t_assert(!"Not implemented!");
            return 0;
        }

        case TypeKind::VarArgType: {
            t_assert(!"Not implemented!");
        } break;
    } // switch (type->kind)
    return 0;
}

i64 Val::evaluate_expr_size(Expr* expr) {
    switch (expr->expr_kind) {
        default: return 0;

        case ExprKind::ArraySubscriptExpr: {
            ArraySubscriptExpr* array_subscript_expr = static_cast<ArraySubscriptExpr*>(expr);

            return 0;

        } break;

        case ExprKind::BinaryOpExpr: {

        } break;

        case ExprKind::BooleanLiteral: {

        } break;

        case ExprKind::CallExpr: {

        } break;

        case ExprKind::CastExpr: {

        } break;

        case ExprKind::CharLiteral: {

        } break;

        case ExprKind::DeclRefExpr: {

        } break;

        case ExprKind::InitalizerExpr: {

        } break;

        case ExprKind::IntegerLiteral: {

        } break;

        case ExprKind::MemberExpr: {

        } break;

        case ExprKind::ParenExpr: {

        } break;

        case ExprKind::RealLiteral: {

        } break;

        case ExprKind::StringLiteral: {

        } break;

        case ExprKind::TernaryExpr: {

        } break;

        case ExprKind::UnaryOpExpr: {

        } break;

    } // switch (expr->expr_kind)
    return 0;
}

BasicKind Val::evaulate_expression_type(Expr* expr) {
    switch (expr->expr_kind) {
        case ExprKind::ArraySubscriptExpr: {
            ArraySubscriptExpr* array_subscript_expr = static_cast<ArraySubscriptExpr*>(expr);
        } break;
    } // switch (expr->expr_kind)
    return BasicKind::Null;
}

} // namespace vc
} // namespace t
