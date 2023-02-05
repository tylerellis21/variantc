#include <vc/compiler/parser.h>

namespace vc {


bool Parser::parse_basic_type(Type** type) {
    *type = new BasicType(loc(), basic_from_token(current.kind));
    consume();
    return true;
}

bool Parser::parse_pointer_type(Type** type) {
    *type = new PointerType(loc(), *type);
    consume();
    return true;
}

bool Parser::parse_declref_type(Type** type, Name* name) {
    //if (!parse_name(&name, true)) return false;
    *type = new DeclRefType(name->loc, name, 0);
    // Don't consume since the parse_name did that for us
    return true;
}

bool Parser::parse_array_type(Type** type) {
    consume();
    // NOTE(Tyler): Does this expression need a parent?
    // How does this effect validation?
    Expr* length = parse_expr(0);
    if (length->expr_kind != ExprKind::IntegerLiteral) {
        report_error(lexer->fb, loc(), "expected integer literal\n");
        return false;
    }
    *type = new ArrayType(loc(), *type, static_cast<IntegerLiteral*>(length)->signed_qword);
    if (!expect_consume(TokenKind::RSquare)) return false;
    return true;
}

bool Parser::parse_vararg_type(Type** type) {
    *type = new VarArgType(loc(), *type);
    consume();
    return true;
}

bool Parser::parse_template_type(Type** type, Name* name) {

    // Perhaps remove this and require the caller pass in a pre parsed name?
    if (!name) if (!parse_name(&name, true)) return false;

    List<Type*> types(1);

    SourceLocation start_loc = loc();
    if (current.kind == TokenKind::At) {
        consume();
    }

    while (valid()) {

        Type* type = 0;
        if (!parse_type(&type)) return false;

        types.push(type);

        //if (current.kind == TokenKind::Greater || current.kind == TokenKind::LParen) break;
        if (current.kind == TokenKind::Comma) {
            consume();
            continue;
        }
        else {
            //report_error(lexer->fb, loc(), "unexpected token in template type");
            break;
        }
    }

    TemplateType* template_type = new TemplateType(start_loc);

    template_type->name = name;
    template_type->types = types;

    if (is_type_token(current.kind)) {
        if (!parse_type(type)) return false;
    }

    *type = template_type;

    return true;
}

bool Parser::parse_type(Type** type, bool first_call) {

    // We break out of the switch in the cases below
    // so that then end of the function can handle recursion if needed
    // we use this for types such as
    // i32**
    // where the first call would parse the 'i32'
    // second call the first '*'
    // and the third would be the last '*'

    switch (current.kind) {

    // We can only parse identifiers as a type on the first call
    // otherwise we risk consuming tokens that aren't part of the type

    case TokenKind::Identifier: {

        Name* name = 0;
        if (!parse_name(&name, true)) return false;

        if (current.kind == TokenKind::Less ||
            current.kind == TokenKind::At)  {
            if (!parse_template_type(type, name)) return false;
        }
        else if (first_call) {
            if (!parse_declref_type(type, name)) return false;
        }
        // Return true since we have hit the end of the type
        // i32** i = 0;
        //       ^
        else return true;
    } break;

    case TokenKind::Star: {
        if (!parse_pointer_type(type)) return false;
    } break;

    case TokenKind::LSquare: {
        if (!parse_array_type(type)) return false;
    } break;

    case TokenKind::Ellipsis: {
        if (!parse_vararg_type(type)) return false;
    } break;

    case TokenKind::Less: {
        if (!parse_template_type(type)) return false;
    } break;

    // Dispatch all basic kinds to the parse basic type method.
    {
        #define BASIC_KIND(KIND, STR, SIZE) case TokenKind::KIND:
        #include <vc/definitions/basic_kinds.def>
        #undef BASIC_KIND

        if (!parse_basic_type(type)) return false;
        break;
    }

    default: {
        report_error(lexer->fb, current.loc, "unexpected token in type: %s\n", token_symbol_or_string(current.kind).buffer);
        return false;
    }

    } // switch (current.kind)

    if (is_type_token(current.kind)) {
        return parse_type(type, false);
    }

    return true;
}

} // namespace vc
