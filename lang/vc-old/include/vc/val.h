#ifndef VAL_H_INCLUDE
#define VAL_H_INCLUDE

#include <vc/ast/decl.h>
#include <vc/ast/expr.h>
#include <vc/ast/stmt.h>
#include <vc/ast/type.h>

#include <vc/ast/recursive_ast_visitor.h>

#include <vc/basic/file_buffer.h>

#include <t/struct/list.h>
#include <t/struct/map.h>

namespace t {
namespace vc {

struct Decl;
struct Stmt;
struct Expr;
struct Type;

struct Module;
struct CompilerFlags;

// 'Val' preforms a critical role in validation of any given AST
// Val will visit each node in a depth first iteration over the AST
// For each node it hits, it will preform various checks the node

struct Val : RecursiveAstVisitor {

    FileBuffer* fb;
    Module* module;

    // Used for "preprocessing"
    CompilerFlags* flags;

    Map<Name, Decl*> local_type_map;

    inline Val(FileBuffer* file_buffer, Module* module, CompilerFlags* flags) :
        fb(file_buffer),
        module(module),
        flags(flags),
        local_type_map(Map<Name, Decl*>())
    { }

    inline bool validate(Decl* decl) {
        return dispatch(decl);
    }

    // Validation Functions

    void duplicate_declaration_found(Decl* a, Decl* b);

    // Check for a duplicate declartion in the declarations local scope.
    // Returns true if a duplicate is found.
    bool local_scope_duplicate_check(Decl* decl);

    // Check for a duplicate typename
    bool global_typename_check(Decl* decl);

    /*
     * What type of searching do we actually need for validation?
     * 	- Search for duplicate declations in the same scope
     *  - Search for shadowed declartions in higher scopes.
     *  - Type name resolution.
     */

    // TODO(@Tyler): Perhaps we move theses functions
    // into their own module?

    // Find's the scope declaration of any given declaration.
    static Decl* find_decl_scope(Decl* decl);
    static Decl* search_decl_scope(Name* name, Decl* scope, Decl* exclude = 0);
    static Decl* search_decl_scope_dg(Name* name, DeclGroup* dg, Decl* exclude = 0);

    // Evaulate the type of a given expression.
    // Depending on the expression this will return the smallest basic kind that will
    // fit the given expression value.

    // This function currently doesn't handle user defined types.
    // I'm not sure where that will fit in yet.
    
    // Calculate the size of a given type in bytes.
    static i64 evaluate_type_size(Type* type);
    static i64 evaluate_expr_size(Expr* expr);
    static BasicKind evaulate_expression_type(Expr* expr);

    //
    // Declarations
    //

    bool visit_Decl(Decl* decl);
    bool visit_EnumDecl(EnumDecl* enum_decl);
    bool visit_EnumConstDecl(EnumConstDecl* enum_const_decl);
    bool visit_ModuleDecl(ModuleDecl* module_decl);
    bool visit_FunctionDecl(FunctionDecl* function_decl);
    bool visit_FunctionArgDecl(FunctionArgDecl* function_arg_decl);
    bool visit_NamespaceDecl(NamespaceDecl* namespace_decl);
    bool visit_PackageDecl(PackageDecl* package_decl);
    bool visit_RecordDecl(RecordDecl* record_decl);
    bool visit_TemplateDecl(TemplateDecl* template_decl);
    bool visit_TemplateNameDecl(TemplateNameDecl* template_name_decl);
    bool visit_TypedefDecl(TypedefDecl* typedef_decl);
    bool visit_UsingDecl(UsingDecl* using_decl);
    bool visit_VarDecl(VarDecl* var_decl);
    bool visit_ImportDecl(ImportDecl* import_decl);
    bool visit_PPIfDecl(PPIfDecl* pp_if_decl);
    bool visit_PPDefDecl(PPDefDecl* pp_def_decl);
    bool visit_PPUndefDecl(PPUndefDecl* pp_undef_decl);

    //
    // Statements
    //

    bool visit_Stmt(Stmt* stmt);
    bool visit_BreakStmt(BreakStmt* break_stmt);
    bool visit_CaseStmt(CaseStmt* case_stmt);
    bool visit_CompoundStmt(CompoundStmt* compound_stmt);
    bool visit_ContinueStmt(ContinueStmt* continue_stmt);
    bool visit_DeclStmt(DeclStmt* decl_stmt);
    bool visit_DefaultStmt(DefaultStmt* default_stmt);
    bool visit_DoStmt(DoStmt* do_stmt);
    bool visit_IfStmt(IfStmt* if_stmt);
    bool visit_LabelStmt(LabelStmt* label_stmt);
    bool visit_GotoStmt(GotoStmt* goto_stmt);
    bool visit_ReturnStmt(ReturnStmt* return_stmt);
    bool visit_SwitchStmt(SwitchStmt* switch_stmt);
    bool visit_WhileStmt(WhileStmt* while_stmt);
    bool visit_ForStmt(ForStmt* for_stmt);

    //
    // Expressions
    //

    bool visit_Expr(Expr* expr);
    bool visit_ArraySubscriptExpr(ArraySubscriptExpr* array_subscript_expr);
    bool visit_BinaryOpExpr(BinaryOpExpr* binary_op_expr);
    bool visit_CallExpr(CallExpr* call_expr);
    bool visit_CastExpr(CastExpr* cast_expr);
    bool visit_TernaryExpr(TernaryExpr* ternary_expr);
    bool visit_DeclRefExpr(DeclRefExpr* decl_ref_expr);
    bool visit_MemberExpr(MemberExpr* member_expr);
    bool visit_ParenExpr(ParenExpr* paren_expr);
    bool visit_UnaryOpExpr(UnaryOpExpr* unary_op_expr);
    bool visit_InitalizerExpr(InitalizerExpr* initalizer_expr);
    bool visit_BooleanLiteral(BooleanLiteral* boolean_literal);
    bool visit_CharLiteral(CharLiteral* char_literal);
    bool visit_IntegerLiteral(IntegerLiteral* integer_literal);
    bool visit_RealLiteral(RealLiteral* real_literal);
    bool visit_StringLiteral(StringLiteral* string_literal);

    //
    // Types
    //

    bool visit_ArrayType(ArrayType* array_type);
    bool visit_BasicType(BasicType* basic_type);
    bool visit_DeclRefType(DeclRefType* decl_ref_type);
    bool visit_PointerType(PointerType* pointer_type);
    bool visit_TemplateType(TemplateType* template_type);
    bool visit_VarArgType(VarArgType* vararg_type);
};

} // namespace vc
} // namespace t

#endif // VAL_H_INCLUDE
