#include <vc/ast/printer.h>
#include <vc/basic/report.h>

#include <iostream>
#include <cassert>

namespace t {
namespace vc {

void AstPrinter::print(Name* name) {
    if (!name) return;
    u64 count = name->identifiers.count;
    bool colon = false;
    for (u64 i = 0; i < count; i++) {
        if (colon) fprintf(m_file, "::");
        fprintf(m_file, "%s", name->identifiers.data[i].buffer);
        colon = true;
    }
}

void AstPrinter::print(Decl* decl) {
    dispatch(decl);
}

void AstPrinter::print(Type* type) {
    dispatch(type);
}

//
// Declarations
//

bool AstPrinter::visit_Decl(Decl* decl) {
    indent();
    return true;
}

bool AstPrinter::visit_EnumDecl(EnumDecl* enum_decl) {
    fprintf(m_file, "EnumDecl '");
    print(enum_decl->full_name);
    fprintf(m_file, "' ");
    if (enum_decl->type) {
        dispatch(enum_decl->type);
        fprintf(m_file, " ");
    }
    print(enum_decl->loc);
    fprintf(m_file, "\n");
/*
    for (EnumConstDecl* entry : enum_decl->entries) {
        //walk()
    }
*/
    return true;
}

bool AstPrinter::visit_EnumConstDecl(EnumConstDecl* enum_const_decl) {
    fprintf(m_file, "EnumConstDecl '");
    print(enum_const_decl->full_name);
    fprintf(m_file, "' ");
    print(enum_const_decl->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_ModuleDecl(ModuleDecl* module_decl) {
    fprintf(m_file, "ModuleDecl\n");
    return true;
}

bool AstPrinter::visit_FunctionDecl(FunctionDecl* function_decl) {
    fprintf(m_file, "FunctionDecl '");
    print(function_decl->full_name);
    fprintf(m_file, "' ");
    dispatch(function_decl->return_type);
    fprintf(m_file, " ");
    print(function_decl->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_FunctionArgDecl(FunctionArgDecl* function_arg_decl) {
    fprintf(m_file, "FunctionArgDecl ");

    if (function_arg_decl->is_var_arg) {
        fprintf(m_file, "...");
    }

    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_NamespaceDecl(NamespaceDecl* namespace_decl) {
    fprintf(m_file, "NamespaceDecl '");
    print(namespace_decl->full_name);
    fprintf(m_file, "' ");
    print(namespace_decl->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_PackageDecl(PackageDecl* package_decl) {
    fprintf(m_file, "PackageDecl '");
    print(package_decl->name);
    fprintf(m_file, "'\n");
    return true;
}

bool AstPrinter::visit_RecordDecl(RecordDecl* record_decl) {
    fprintf(m_file, "RecordDecl ");

    switch (record_decl->record_kind) {
    default: break;
    case RecordKind::StructKind: fprintf(m_file, "struct"); break;
    case RecordKind::UnionKind: fprintf(m_file, "record"); break;
    }

    fprintf(m_file, " '");
    print(record_decl->full_name);
    fprintf(m_file, "' ");
    print(record_decl->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_TemplateDecl(TemplateDecl* template_decl) {
    fprintf(m_file, "TemplateDecl ");
    print(template_decl->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_TemplateNameDecl(TemplateNameDecl* template_name_decl) {
    fprintf(m_file, "TemplateNameDecl '");
    print(template_name_decl->full_name);
    fprintf(m_file, "' ");
    print(template_name_decl->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_TypedefDecl(TypedefDecl* typedef_decl) {
    fprintf(m_file, "TypedefDecl ");
    print(typedef_decl->type);
    fprintf(m_file, " '");
    print(typedef_decl->name);
    fprintf(m_file, "' ");
    print(typedef_decl->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_UsingDecl(UsingDecl* using_decl) {
    fprintf(m_file, "UsingDecl '");
    print(using_decl->name);
    fprintf(m_file, "' ");
    print(using_decl->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_VarDecl(VarDecl* var_decl) {
    fprintf(m_file, "VarDecl '");
    print(var_decl->full_name);
    fprintf(m_file, "' ");
    print(var_decl->type);
    fprintf(m_file, " ");
    if (var_decl->bitsize > 0) {
        fprintf(m_file, ": %i ", var_decl->bitsize);
    }
    print(var_decl->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_ImportDecl(ImportDecl* import_decl) {
    fprintf(m_file, "ImportDecl '");
    print(import_decl->name);
    fprintf(m_file, "' ");
    print(import_decl->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_PPIfDecl(PPIfDecl* pp_if_decl) {
    fprintf(m_file, "PPIfDecl ");
    print(pp_if_decl->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_PPDefDecl(PPDefDecl* pp_def_decl) {
    fprintf(m_file, "PPDefDecl ");
    print(pp_def_decl->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_PPUndefDecl(PPUndefDecl* pp_undef_decl) {
    fprintf(m_file, "PPUndefDecl ");
    print(pp_undef_decl->loc);
    fprintf(m_file, "\n");
    return true;
}

//
// Statements
//

bool AstPrinter::visit_Stmt(Stmt* stmt) {
    indent();
    return true;
}

bool AstPrinter::visit_BreakStmt(BreakStmt* break_stmt) {
    fprintf(m_file, "BreakStmt ");
    print(break_stmt->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_CaseStmt(CaseStmt* case_stmt) {
    fprintf(m_file, "CaseStmt ");
    print(case_stmt->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_CompoundStmt(CompoundStmt* compound_stmt) {
    fprintf(m_file, "CompoundStmt ");
    print(compound_stmt->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_ContinueStmt(ContinueStmt* continue_stmt) {
    fprintf(m_file, "ContinueStmt ");
    print(continue_stmt->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_DeclStmt(DeclStmt* decl_stmt) {
    fprintf(m_file, "DeclStmt ");
    print(decl_stmt->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_DefaultStmt(DefaultStmt* default_stmt) {
    fprintf(m_file, "DefaultStmt ");
    print(default_stmt->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_DoStmt(DoStmt* do_stmt) {
    fprintf(m_file, "DoStmt ");
    print(do_stmt->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_IfStmt(IfStmt* if_stmt) {
    fprintf(m_file, "IfStmt ");
    print(if_stmt->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_LabelStmt(LabelStmt* label_stmt) {
    fprintf(m_file, "LabelStmt '");
    print(label_stmt->name);
    fprintf(m_file, "' ");
    print(label_stmt->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_GotoStmt(GotoStmt* goto_stmt) {
    fprintf(m_file, "GotoStmt '");
    print(goto_stmt->name);
    fprintf(m_file, "' ");
    print(goto_stmt->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_ReturnStmt(ReturnStmt* return_stmt) {
    fprintf(m_file, "ReturnStmt ");
    print(return_stmt->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_SwitchStmt(SwitchStmt* switch_stmt) {
    fprintf(m_file, "SwitchStmt ");
    print(switch_stmt->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_WhileStmt(WhileStmt* while_stmt) {
    fprintf(m_file, "WhileStmt ");
    print(while_stmt->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_ForStmt(ForStmt* for_stmt) {
    fprintf(m_file, "ForStmt ");
    print(for_stmt->loc);
    fprintf(m_file, "\n");
    return true;
}

//
// Expressions
//

bool AstPrinter::visit_Expr(Expr* expr) {
    indent();
    return true;
}

bool AstPrinter::visit_ArraySubscriptExpr(ArraySubscriptExpr* array_subscript_expr) {
    fprintf(m_file, "ArraySubscriptExpr ");
    print(array_subscript_expr->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_BinaryOpExpr(BinaryOpExpr* binary_op_expr) {
    fprintf(m_file, "BinaryOpExpr %s ", token_str(binary_op_expr->op).buffer);
    print(binary_op_expr->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_CallExpr(CallExpr* call_expr) {
    fprintf(m_file, "CallExpr '");

    if (call_expr->template_type)
        print(call_expr->template_type);
    else
        print(call_expr->name);

    fprintf(m_file, "' ");
    print(call_expr->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_CastExpr(CastExpr* cast_expr) {
    fprintf(m_file, "CastExpr ");
    print(cast_expr->type);
    fprintf(m_file, " ");
    print(cast_expr->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_TernaryExpr(TernaryExpr* ternary_expr) {
    fprintf(m_file, "TernaryExpr ");
    print(ternary_expr->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_DeclRefExpr(DeclRefExpr* decl_ref_expr) {
    fprintf(m_file, "DeclRefExpr '");
    print(decl_ref_expr->name);
    fprintf(m_file, "' ");
    print(decl_ref_expr->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_MemberExpr(MemberExpr* member_expr) {
    fprintf(m_file, "MemberExpr '");
    print(member_expr->name);
    fprintf(m_file, "' \n");
    return true;
}

bool AstPrinter::visit_ParenExpr(ParenExpr* paren_expr) {
    fprintf(m_file, "ParenExpr ");
    print(paren_expr->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_UnaryOpExpr(UnaryOpExpr* unary_op_expr) {
    fprintf(m_file, "UnaryOpExpr '%s' ", token_str(unary_op_expr->op).buffer);
    if (unary_op_expr->postfix) fprintf(m_file, "Postfix ");
    else fprintf(m_file, "Prefix ");
    print(unary_op_expr->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_InitalizerExpr(InitalizerExpr* initalizer_expr) {
    fprintf(m_file, "InitalizerExpr ");
    print(initalizer_expr->loc);
    fprintf(m_file, "\n");
    for (Expr* value : initalizer_expr->values) {
        dispatch(value);
    }
    return true;
}

bool AstPrinter::visit_BooleanLiteral(BooleanLiteral* boolean_literal) {
    fprintf(m_file, "BooleanlLiteral '");
    if (boolean_literal->value) fprintf(m_file, "true' ");
    else fprintf(m_file, "false' ");
    print(boolean_literal->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_CharLiteral(CharLiteral* char_literal) {
    fprintf(m_file, "CharLiteral '%c' ", char_literal->value);
    print(char_literal->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_IntegerLiteral(IntegerLiteral* integer_literal) {
    if (integer_literal->is_signed)
        fprintf(m_file, "IntegerLiteral '%llx' ", integer_literal->signed_qword);
    else
        fprintf(m_file, "IntegerLiteral '%llx' ", integer_literal->unsigned_qword);
    print(integer_literal->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_RealLiteral(RealLiteral* real_literal) {
    if (real_literal->real_kind == RealKind::Real32)
        fprintf(m_file, "RealLiteral '%f' ", real_literal->real32);
    else
        fprintf(m_file, "RealLiteral '%f' ", real_literal->real64);
    print(real_literal->loc);
    fprintf(m_file, "\n");
    return true;
}

bool AstPrinter::visit_StringLiteral(StringLiteral* string_literal) {
    fprintf(m_file, "StringLiteral '%s' ", string_literal->value.buffer);
    print(string_literal->loc);
    fprintf(m_file, "\n");
    return true;
}

//
// Types
//

bool AstPrinter::visit_ArrayType(ArrayType* array_type) {
    fprintf(m_file, "[%llu]", array_type->length);
    return true;
}

bool AstPrinter::visit_BasicType(BasicType* basic_type) {
    utf8 str = basic_kind_str(basic_type->basic_kind);
    fprintf(m_file, "%s", str.buffer);
    return true;
}

bool AstPrinter::visit_DeclRefType(DeclRefType* decl_ref_type) {
    print(decl_ref_type->name);
    return true;
}

bool AstPrinter::visit_PointerType(PointerType* pointer_type) {
    fprintf(m_file, "*");
    return true;
}

bool AstPrinter::visit_TemplateType(TemplateType* template_type) {
    if (template_type->name) print(template_type->name);

    bool first = true;

    if (template_type->types.count > 0) {
        fprintf(m_file, "@");
        for (Type* t : template_type->types) {
            if (!first) fprintf(m_file, ",");
            first = false;
            dispatch(t);
        }
        fprintf(m_file, " ");
    }
    return true;
}

bool AstPrinter::visit_VarArgType(VarArgType* vararg_type) {
    fprintf(m_file, "...");
    return true;
}

} // namespace vc
} // namespace t

