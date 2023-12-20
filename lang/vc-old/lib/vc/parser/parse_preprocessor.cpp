#include <vc/parser.h>

namespace t {
namespace vc {

bool eval_condition(Expr* condition) {
    return false;
}

bool Parser::parse_pp_decl(Decl* parent, DeclGroup* dg) {
    // consume the '@' symbol
    SourceLocation start_loc = consume();

    switch (current.kind) {
    default: return false;

    case TokenKind::If:  {
        PPIfDecl* pp_if_decl = 0;
        if (!parse_pp_if_decl(parent, &pp_if_decl)) return false;

        if (eval_condition(pp_if_decl->condition)) {

        }

        dg->add(pp_if_decl);
    } break;

    case TokenKind::Define: {
        SourceLocation loc = consume();

        Name* name = 0;
        if (!parse_name(&name, true)) return false;

        PPDefDecl* decl = new PPDefDecl(loc, parent, name);

        dg->add(decl);
        if (!expect_semi()) return false;
    } break;

    case TokenKind::Undefine: {
        SourceLocation loc = consume();

        Name* name = 0;
        if (!parse_name(&name, true)) return false;

        PPUndefDecl* decl = new PPUndefDecl(loc, parent, name);

        dg->add(decl);
        if (!expect_semi()) return false;
    } break;

    } // switch (current.kind)

    return true;
}

bool Parser::parse_pp_if_decl(Decl* parent, PPIfDecl** out) {

    SourceLocation keyword_loc = consume();

    SourceLocation start_loc = loc();
    if (!expect_consume(TokenKind::LParen)) return false;

    Expr* expr = parse_cast_expr(0);

    SourceLocation end_loc = loc();
    if (!expect_consume(TokenKind::RParen)) return false;

    PPIfDecl* pp_if_decl = new PPIfDecl(keyword_loc, parent);

    pp_if_decl->condition = expr;
    pp_if_decl->dg = new DeclGroup(0);

    if (!parse_pp_decl_group(pp_if_decl, pp_if_decl->dg)) return false;

    if (current.kind == TokenKind::Else) {
        consume();
        if (!parse_pp_if_decl(pp_if_decl, &pp_if_decl->else_stmt)) return false;
    }

    *out = pp_if_decl;

    return true;
}

bool Parser::parse_pp_decl_group(Decl* parent, DeclGroup* dg) {

    SourceLocation brace_open_loc = loc();
    if (!expect_consume(TokenKind::LBrace)) return false;

    while (valid()) {
        if (current.kind == TokenKind::RBrace) break;
        if (!parse_top_level_decl(parent, dg)) return false;
    }

    SourceLocation brace_close_loc = loc();
    if (!expect_consume(TokenKind::RBrace)) return false;

    return true;
}

} // namespace vc
} // namespace t
