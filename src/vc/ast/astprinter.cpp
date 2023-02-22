#include <vc/ast/astprinter.h>

#include <vc/ast/decl.h>
#include <vc/ast/declgroup.h>
#include <vc/ast/expr.h>
#include <vc/ast/name.h>
#include <vc/ast/stmt.h>
#include <vc/ast/type.h>

namespace vc {

void printIndent(i32 indent) {
    for (int i = 0; i < indent; i++) {
        std::cout << " ";
    }
}

void printDecl(Decl* decl, i32 indent) {
    printIndent(indent);
    switch (decl->declKind) {

        case DeclKind::EnumConstDecl: {
            std::cout << "[EnumConstDecl]";
        } break;

        case DeclKind::EnumDecl: {
            std::cout << "[EnumConstDecl]";
        } break;

        case DeclKind::FunctionArgDecl: {
            std::cout << "[FunctionArgDecl]";
        } break;

        case DeclKind::FunctionDecl: {
            std::cout << "[FunctionDecl]";
        } break;

        case DeclKind::ImportDecl: {
            std::cout << "[ImportDecl]";
        } break;

        case DeclKind::InterfaceDecl: {
            std::cout << "[InterfaceDecl]";
        } break;

        case DeclKind::ModuleDecl: {
            std::cout << "[ModuleDecl]";
        } break;

        case DeclKind::NamespaceDecl: {
            std::cout << "[NamespaceDecl]";
        } break;

        case DeclKind::PackageDecl: {
            std::cout << "[PackageDecl]";
        } break;

        case DeclKind::PPDefDecl: {
            std::cout << "[PPDefDecl]";
        } break;

        case DeclKind::PPIfDecl: {
            std::cout << "[PPIfDecl]";
        } break;

        case DeclKind::PPUndefDecl: {
            std::cout << "[PPUndefDecl]";
        } break;

        case DeclKind::RecordDecl: {
            std::cout << "[RecordDecl]";
        } break;

        case DeclKind::TypedefDecl: {
            std::cout << "[TypedefDecl]";
        } break;

        case DeclKind::UsingDecl: {
            std::cout << "[UsingDecl]";
        } break;

        case DeclKind::VarDecl: {
            std::cout << "[VarDecl]";
        } break;

        default:
            std::cout << "Unhandled decl kind in ast printer" << std::endl;
        break;
    }
}

void printDeclGroup(DeclGroup* declGroup, i32 indent) {
    for (int i = 0; i < declGroup->entries.size(); i++) {
        Decl* decl = declGroup->entries[i];
        printDecl(decl, indent + 1);
    }
}

void printStmt(Stmt* stmt, i32 indent) {
    printIndent(indent);
    switch (stmt->stmtKind) {

        case StmtKind::BreakStmt: {
            std::cout << "[BreakStmt]";
        } break;

        case StmtKind::CaseStmt: {
            std::cout << "[CaseStmt]";
        } break;

        case StmtKind::CompoundStmt: {
            std::cout << "[CompoundStmt]";
        } break;

        case StmtKind::ContinueStmt: {
            std::cout << "[ContinueStmt]";
        } break;

        case StmtKind::DeclStmt: {
            std::cout << "[DeclStmt]";
        } break;

        case StmtKind::DefaultStmt: {
            std::cout << "[DefaultStmt]";
        } break;

        case StmtKind::DeferStmt: {
            std::cout << "[DeferStmt]";
        } break;

        case StmtKind::DoStmt: {
            std::cout << "[DoStmt]";
        } break;

        case StmtKind::ExprStmt: {
            std::cout << "[ExprStmt]";
        } break;

        case StmtKind::ForStmt: {
            std::cout << "[ForStmt]";
        } break;

        case StmtKind::GotoStmt: {
            std::cout << "[GotoStmt]";
        } break;

        case StmtKind::IfStmt: {
            std::cout << "[IfStmt]";
        } break;

        case StmtKind::LabelStmt: {
            std::cout << "[LabelStmt]";
        } break;

        case StmtKind::ReturnStmt: {
            std::cout << "[ReturnStmt]";
        } break;

        case StmtKind::SwitchStmt: {
            std::cout << "[SwitchStmt]";
        } break;

        case StmtKind::UseStmt: {
            std::cout << "[UseStmt]";
        } break;

        case StmtKind::WhileStmt: {
            std::cout << "[WhileStmt]";
        } break;

        default:
            std::cout << "Unhandled stmt kind in ast printer" << std::endl;
        break;
    }
}

void printExpr(Expr* expr, i32 indent) {
    printIndent(indent);
    switch (expr->exprKind) {
        case ExprKind::ArraySubscriptExpr: {
            std::cout << "[ArraySubscriptExpr]";
        } break;

        case ExprKind::BinaryOpExpr: {
            std::cout << "[BinaryOpExpr]";
        } break;

        case ExprKind::CallExpr: {
            std::cout << "[CallExpr]";
        } break;

        case ExprKind::CastExpr: {
            std::cout << "[CastExpr]";
        } break;

        case ExprKind::DeclRefExpr: {
            std::cout << "[DeclRefExpr]";
        } break;

        case ExprKind::InitalizerExpr: {
            std::cout << "[InitalizerExpr]";
        } break;

        case ExprKind::MemberExpr: {
            std::cout << "[MemberExpr]";
        } break;

        case ExprKind::ParenExpr: {
            std::cout << "[ParenExpr]";
        } break;

        case ExprKind::TernaryExpr: {
            std::cout << "[TernaryExpr]";
        } break;

        case ExprKind::UnaryOpExpr: {
            std::cout << "[UnaryOpExpr]";
        } break;

        case ExprKind::BooleanLiteralExpr: {
            std::cout << "[BooleanLiteralExpr]";
        } break;

        case ExprKind::CharLiteralExpr: {
            std::cout << "[CharLiteralExpr]";
        } break;

        case ExprKind::IntegerLiteralExpr: {
            std::cout << "[IntegerLiteralExpr]";
        } break;

        case ExprKind::RealLiteralExpr: {
            std::cout << "[RealLiteralExpr]";
        } break;

        case ExprKind::StringLiteralExpr: {
            std::cout << "[StringLiteralExpr]";
        } break;

        default:
            std::cout << "Unhandled expr kind in ast printer" << std::endl;
        break;
    }
}

void printType(Type* type) {
    switch (type->typeKind) {
        case TypeKind::ArrayType: {
            std::cout << "[ArrayType]";
        } break;

        case TypeKind::BuiltinType: {
            std::cout << "[BuiltinType]";
        } break;

        case TypeKind::DeclRefType: {
            std::cout << "[DeclRefType]";
        } break;

        case TypeKind::PointerType: {
            std::cout << "[PointerType]";
        } break;

        default:
            std::cout << "Unhandled type kind in ast printer" << std::endl;
        break;
    }
}

} // namespace vc