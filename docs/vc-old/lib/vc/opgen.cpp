#include <vc/opgen.h>
#include <vc/basic/report.h>

//#include <vc/val.h>

namespace t {
namespace vc {

bool OPGen::traverse_ModuleDecl(ModuleDecl* module_decl)  {
    
    // The top generation result is the .init section of a module.
    Name* name = new Name;
    name->identifiers.push(utf8(".init"));
    function_stack.push(new OPGenFunction(name));

    RIFN(visit_ModuleDecl(module_decl));
    RIFN(traverse_DeclGroup(module_decl->dg));

    functions.push(function_stack.pop());
    return true;
}

bool OPGen::traverse_FunctionDecl(FunctionDecl* function_decl) {
    
    OPGenFunction* function = new OPGenFunction(function_decl->name);
    
    function_stack.push(function);

    for (FunctionArgDecl* arg : function_decl->args) RIFN(dispatch(arg));
    //RIFN(dispatch(function_decl->return_type));
    //RIFN(dispatch(function_decl->template_decl));
    RIFN(dispatch(function_decl->body));

    function_stack.pop();
    functions.push(function);
    
    return true;
}

// In the case of variables we want to visit the node before dispatching
bool OPGen::traverse_VarDecl(VarDecl* var_decl) {
    RIFN(dispatch(var_decl->assignment));
    RIFN(visit_VarDecl(var_decl));
    return true;
}

bool OPGen::visit_VarDecl(VarDecl* var_decl) {
    OPGenFunction* function = function_stack.top();
    
    Name* full_name = var_decl->full_name;

    // Determine if this declaration is a global variable or a local one.
    bool is_local = is_local_declaration(var_decl);

    if (is_local) {
        u16 index = function->local_index++;
        function->local_map.set(*full_name, index);

        printf("mapped ");
        name_print(full_name);
        printf(" -> %%%i\n", index);

        // If we have an assignment expression that
        // will leave us a value on the stack that we need to store.
        if (var_decl->assignment) {
            Opcode op(LSTORE);
            op.lstore.address = index;
            op.lstore.type = OpcodeType::type_i32;
            function->opcodes.push(op);
        }
    }
    else {
        u16 index = global_index++;
        global_map.set(*full_name, index);

        printf("mapped ");
        name_print(full_name);
        printf(" -> $%i\n", index);

        if (var_decl->assignment) {
            Opcode op(STORE);
            op.store.address = index;
            op.store.type = OpcodeType::type_i32;
            function->opcodes.push(op);
        }
    }

    return true;
}

bool OPGen::visit_ReturnStmt(ReturnStmt* stmt) {
    OPGenFunction* function = function_stack.top();
    function->opcodes.push(Opcode(RET));
    return true;
}

bool OPGen::visit_IntegerLiteral(IntegerLiteral* value) {

    OPGenFunction* function = function_stack.top();

    // TODO(@Tyler): Figure out the smallest number of
    // bytes needed to save the value.
    Opcode op_push(PUSH64);
    op_push.push64.value = value->signed_qword; 
    
    if (function) function->opcodes.push(op_push);
    
    return true;
}

bool OPGen::visit_BinaryOpExpr(BinaryOpExpr* binary_op_expr) {
    OPGenFunction* function = function_stack.top();
    
    OpcodeType op_type = OpcodeType::type_i64;

    switch (binary_op_expr->op) {
    
        case TokenKind::Plus: {
            Opcode op(ADD);
            op.add.type = op_type;
            function->opcodes.push(op);
        } break;
        
        case TokenKind::PlusPlus: {
            Opcode op(INC);
            op.inc.type = op_type;
            function->opcodes.push(op);
        } break;

        case TokenKind::Minus: {
            Opcode op(SUB);
            op.sub.type = op_type;
            function->opcodes.push(op);
        } break;
        
        case TokenKind::MinusMinus: {
            Opcode op(DEC);
            op.dec.type = op_type;
            function->opcodes.push(op);
        } break;

        case TokenKind::Star: {
            Opcode op(MUL);
            op.mul.type = op_type;
            function->opcodes.push(op);
        } break;

        case TokenKind::Slash: {
            Opcode op(DIV);
            op.div.type = op_type;
            function->opcodes.push(op);
        } break;
        
        case TokenKind::Percent: {
            Opcode op(MOD);
            op.mod.type = op_type;
            function->opcodes.push(op);
        } break;
    }
    return true;
}

bool OPGen::visit_DeclRefExpr(DeclRefExpr* decl_ref_expr) {
    
    decl_ref_expr->scope;

    return true;
}

} // namespace vc
} // namespace t
