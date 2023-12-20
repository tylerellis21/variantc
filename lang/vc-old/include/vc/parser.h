#ifndef PARSER_H_INCLUDE
#define PARSER_H_INCLUDE

#include <vc/ast/decl.h>
#include <vc/ast/expr.h>
#include <vc/ast/name.h>
#include <vc/ast/stmt.h>
#include <vc/ast/type.h>
#include <vc/basic/token.h>
#include <vc/basic/report.h>
#include <vc/lexer.h>

#include <t/struct/rbtree.h>

namespace t {
namespace vc {

struct Module;

struct Parser {

    bool failed;

    Token behind;
    Token current;
    Token ahead;

    Lexer* lexer;
    Module* module;

    // preprocesser defines
    RBTree<Name> pp_defs;

    inline Parser(Lexer* lexer, Module* module) :
        lexer(lexer),
        module(module),
        pp_defs(RBTree<Name>()) {
    }

    bool open();

    bool parse(Decl** result);

    inline bool valid() {
        return lexer->has_tokens();
    }

    inline SourceLocation loc() {
        return current.loc;
    }

    // Consume a token advancing the token stream using the underlying lexer provided by the constructor
    SourceLocation consume();

    bool expect_kind(TokenKind kind);
    bool expect_consume(TokenKind kind);

    inline bool expect_semi() {
        if (current.kind != TokenKind::Semi) {
            report_error(lexer->fb, current.loc, "expected semicolon ';'\n");
            return false;
        }
        consume();
        return true;
    }

    bool parse_name(Name** name, bool long_name);

    ///
    /// Declaration parsing methods
    ///

    // One of the core methods being used to parse declarations.
    bool parse_top_level_decl(Decl* parent, DeclGroup* dg);
    bool parse_package_decl(Decl* parent, DeclGroup* dg);
    bool parse_using_decl(Decl* parent, DeclGroup* dg);
    bool parse_typedef_decl(Decl* parent, DeclGroup* dg);
    bool parse_template_decl(Decl* parent, Decl** out);
    bool parse_import_decl(Decl* parent, DeclGroup* dg);
    bool parse_enum_decl(Decl* parent, DeclGroup* dg);
    bool parse_namespace_decl(Decl* parent, DeclGroup* dg);
    bool parse_record_decl(Decl* parent, DeclGroup* dg);
    bool parse_function_decl(Decl* parent, DeclGroup* dg);
    bool parse_function_arg_decl(Decl* parent, FunctionArgDecl** out);
    bool parse_single_var_decl(Decl* parent, VarDecl** out, Type* type = 0);
    bool parse_compound_var_decl(Decl* parent, DeclGroup* dg, Type* type = 0);

    // Preprocesser parsing
    bool parse_pp_decl(Decl* parent, DeclGroup* dg);
    bool parse_pp_if_decl(Decl* parent, PPIfDecl** out);
    bool parse_pp_decl_group(Decl* parent, DeclGroup* dg);

    ///
    /// Statment parsing methods
    ///

    bool parse_stmt(Stmt* stmt_parent, Stmt** out);

    bool parse_compound_stmt(Stmt* stmt_parent, Stmt** out);
    bool parse_optional_compound_stmt(Stmt* stmt_parent, Stmt** out);

    bool parse_break_stmt(Stmt* parent, Stmt** out);
    bool parse_continue_stmt(Stmt* parent, Stmt** out);

    bool parse_template_stmt(Stmt* stmt_parent, Stmt** out);
    bool parse_decl_stmt(Stmt* stmt_parent, Stmt** out);
    bool parse_do_stmt(Stmt* stmt_parent, Stmt** out);
    bool parse_for_stmt(Stmt* stmt_parent, Stmt** out);
    bool parse_if_stmt(Stmt* stmt_parent, Stmt** out);
    bool parse_label_stmt(Stmt* parent, Stmt** out);
    bool parse_goto_stmt(Stmt* parent, Stmt** out);
    bool parse_switch_stmt(Stmt* stmt_parent, Stmt** out);
    bool parse_while_stmt(Stmt* stmt_parent, Stmt** out);
    bool parse_default_stmt(Stmt* stmt_parent, Stmt** out);
    bool parse_case_stmt(Stmt* stmt_parent, Stmt** out);
    bool parse_return_stmt(Stmt* stmt_parent, Stmt** out);
 
    ///
    /// Expression parsing methods
    ///

    Expr* expr_error();

    Expr* parse_expr(Stmt* stmt_parent);
    Expr* parse_assignment_expr(Stmt* stmt_parent);
    Expr* parse_array_subscript_expr(Stmt* stmt_parent, Expr* lhs);
    Expr* parse_unary_expr(Stmt* stmt_parent, Expr* lhs, bool postfix);
    Expr* parse_rhs_binary_op(Stmt* stmt_parent, Expr* lhs, i32 min_precedence);
    Expr* parse_call_expr(Stmt* stmt_parent, bool expect_semi, Name* name = 0, Type* template_type = 0);
    Expr* parse_cast_expr(Stmt* stmt_parent);
    Expr* parse_ternary_expr(Stmt* stmt_parent, Expr* condition);
    Expr* parse_postfix_expr(Stmt* stmt_parent, Expr* lhs, bool postfix);
    Expr* parse_decl_ref_expr(Stmt* stmt_parent);
    Expr* parse_initalizer_expr(Stmt* stmt_parent);
    Expr* parse_literal_expr(Stmt* stmt_parent);
    Expr* parse_paren_expr(Stmt* stmt_parent);
    Expr* parse_member_expr(Stmt* stmt_parent);

    ///
    /// Type parsing methods
    ///

    bool parse_type(Type** type, bool first_call = true);

    bool parse_basic_type(Type** type);
    bool parse_pointer_type(Type** type);
    bool parse_declref_type(Type** type, Name* name = 0);
    bool parse_array_type(Type** type);
    bool parse_vararg_type(Type** type);

    bool parse_template_type(Type** type, Name* name = 0);
};

} // namespace vc
} // namespace t

#endif // PARSER_H_INCLUDE
