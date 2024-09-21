#include <vc/val.h>
#include <vc/compiler.h>
#include <vc/basic/report.h>

namespace t {
namespace vc {

bool Val::visit_Stmt(Stmt* stmt) {
    return true;
}

bool Val::visit_BreakStmt(BreakStmt* break_stmt) {
    return true;
}

bool Val::visit_CaseStmt(CaseStmt* case_stmt) {
    return true;
}

bool Val::visit_CompoundStmt(CompoundStmt* compound_stmt) {
    return true;
}

bool Val::visit_ContinueStmt(ContinueStmt* continue_stmt) {
    return true;
}

bool Val::visit_DeclStmt(DeclStmt* decl_stmt) {
    return true;
}

bool Val::visit_DefaultStmt(DefaultStmt* default_stmt) {
    return true;
}

bool Val::visit_DoStmt(DoStmt* do_stmt) {
    return true;
}

bool Val::visit_IfStmt(IfStmt* if_stmt) {
    return true;
}

bool Val::visit_LabelStmt(LabelStmt* label_stmt) {
    return true;
}

bool Val::visit_GotoStmt(GotoStmt* goto_stmt) {
    return true;
}

bool Val::visit_ReturnStmt(ReturnStmt* return_stmt) {
    return true;
}

bool Val::visit_SwitchStmt(SwitchStmt* switch_stmt) {
    return true;
}

bool Val::visit_WhileStmt(WhileStmt* while_stmt) {
    return true;
}

bool Val::visit_ForStmt(ForStmt* for_stmt) {
    return true;
}

} // namespace vc
} // namespace t
