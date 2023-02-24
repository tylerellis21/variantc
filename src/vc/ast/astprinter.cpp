#include <vc/ast/astprinter.h>

#include <vc/ast/decl.h>
#include <vc/ast/declgroup.h>
#include <vc/ast/expr.h>
#include <vc/ast/name.h>
#include <vc/ast/stmt.h>
#include <vc/ast/type.h>

namespace vc {

void printIndent(i32 indent) {
    for (int i = 0; i < indent - 1; i++) {
        std::cout << "   ";
    }
}

void printDecl(Decl* decl, i32 indent) {
    printIndent(indent);
    switch (decl->declKind) {

        case DeclKind::EnumConstDecl: {
            EnumConstDecl* enumConstDecl = static_cast<EnumConstDecl*>(decl);
            std::cout << "[EnumConstDecl]" << std::endl;
            printExpr(enumConstDecl->value, indent + 1);
        } break;

        case DeclKind::EnumDecl: {
            EnumDecl* enumDecl = static_cast<EnumDecl*>(decl);
            std::cout << "[EnumConstDecl]";

            if (enumDecl->type) {
                std::cout << " : ";
                printType(enumDecl->type);
            }
            std::cout << std::endl;

            printDeclGroup(enumDecl->declGroup, indent + 1);
        } break;

        case DeclKind::FunctionArgDecl: {
            FunctionArgDecl* functionArgDecl = static_cast<FunctionArgDecl*>(decl);
            std::cout << "[FunctionArgDecl]" << std::endl;
            printDecl(functionArgDecl->varDecl, indent + 1);
        } break;

        case DeclKind::FunctionDecl: {
            FunctionDecl* functionDecl = static_cast<FunctionDecl*>(decl);
            std::cout << "[FunctionDecl] '" << functionDecl->name << "' ReturnType: ";
            printType(functionDecl-> returnType);
            std::cout << std::endl;
            for (int i = 0; i < functionDecl->args.size(); i++) {
                Decl* functionArgDecl = functionDecl->args[i];
                printDecl(functionArgDecl, indent + 1);
            }
            printStmt(functionDecl->body, indent + 1);
        } break;

        case DeclKind::ImportDecl: {
            ImportDecl* importDecl = static_cast<ImportDecl*>(decl);
            std::cout << "[ImportDecl] '" << importDecl->name  << "'" << std::endl;
        } break;

        case DeclKind::ModuleDecl: {
            ModuleDecl* moduleDecl = static_cast<ModuleDecl*>(decl);
            std::cout << "[ModuleDecl]" << std::endl;
            printDeclGroup(moduleDecl->declGroup, indent + 1);
        } break;

        case DeclKind::NamespaceDecl: {
            NamespaceDecl* namespaceDecl = static_cast<NamespaceDecl*>(decl);
            std::cout << "[NamespaceDecl] '" << namespaceDecl->name << "'" << std::endl;
            printDeclGroup(namespaceDecl->declGroup, indent + 1);
        } break;

        case DeclKind::PackageDecl: {
            PackageDecl* packageDecl = static_cast<PackageDecl*>(decl);
            std::cout << "[PackageDecl] '" << packageDecl->name << "'" << std::endl;
        } break;

        case DeclKind::PPDefDecl: {
            std::cout << "[PPDefDecl]" << std::endl;
        } break;

        case DeclKind::PPIfDecl: {
            std::cout << "[PPIfDecl]" << std::endl;
        } break;

        case DeclKind::PPUndefDecl: {
            std::cout << "[PPUndefDecl]" << std::endl;
        } break;

        case DeclKind::RecordDecl: {
            RecordDecl* recordDecl = static_cast<RecordDecl*>(decl);
            std::cout << "[RecordDecl] '" << recordDecl->name << "' ";
            switch (recordDecl->recordKind) {
                case RecordKind::AllocatorKind: std::cout << "Allocator"; break;
                case RecordKind::AttributeKind: std::cout << "Attribute"; break;
                case RecordKind::StructKind: std::cout << "Struct"; break;
                case RecordKind::InterfaceKind: std::cout << "Interface"; break;
            }
            std::cout << std::endl;
            printDeclGroup(recordDecl->declGroup, indent + 1);
        } break;

        case DeclKind::TypedefDecl: {
            TypedefDecl* typedefDecl = static_cast<TypedefDecl*>(decl);
            std::cout << "[TypedefDecl] '" << typedefDecl->name << "' ";
            printType(typedefDecl->type);
            std::cout << std::endl;
        } break;

        case DeclKind::UsingDecl: {
            UsingDecl* usingDecl = static_cast<UsingDecl*>(decl);
            std::cout << "[UsingDecl] '" << usingDecl->name << "'" << std::endl;
        } break;

        case DeclKind::VarDecl: {
            VarDecl* varDecl = static_cast<VarDecl*>(decl);
            std::cout << "[VarDecl] '" << varDecl->name << "' ";
            printType(varDecl->type);
            std::cout << std::endl;
            if (varDecl->bitsize) {
                printExpr(varDecl->bitsize, indent + 1);
            }
            if (varDecl->assignment) {
                printExpr(varDecl->assignment, indent + 1);
            }
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
            std::cout << "[BreakStmt]" << std::endl;
        } break;

        case StmtKind::CaseStmt: {
            CaseStmt* caseStmt = static_cast<CaseStmt*>(stmt);
            std::cout << "[CaseStmt]" << std::endl;
        } break;

        case StmtKind::CompoundStmt: {
            CompoundStmt* compoundStmt = static_cast<CompoundStmt*>(stmt);
            std::cout << "[CompoundStmt]" << std::endl;
        } break;

        case StmtKind::ContinueStmt: {
            std::cout << "[ContinueStmt]" << std::endl;
        } break;

        case StmtKind::DeclStmt: {
            DeclStmt* declStmt = static_cast<DeclStmt*>(stmt);
            std::cout << "[DeclStmt]" << std::endl;
        } break;

        case StmtKind::DefaultStmt: {
            DefaultStmt* defaultStmt = static_cast<DefaultStmt*>(stmt);
            std::cout << "[DefaultStmt]" << std::endl;
        } break;

        case StmtKind::DeferStmt: {
            DeferStmt* deferStmt = static_cast<DeferStmt*>(stmt);
            std::cout << "[DeferStmt]" << std::endl;
        } break;

        case StmtKind::DoStmt: {
            DoStmt* doStmt = static_cast<DoStmt*>(stmt);
            std::cout << "[DoStmt]" << std::endl;
        } break;

        case StmtKind::ExprStmt: {
            ExprStmt* exprStmt = static_cast<ExprStmt*>(stmt);
            std::cout << "[ExprStmt]" << std::endl;
        } break;

        case StmtKind::ForStmt: {
            ForStmt* forStmt = static_cast<ForStmt*>(stmt);
            std::cout << "[ForStmt]" << std::endl;
        } break;

        case StmtKind::GotoStmt: {
            GotoStmt* gotoStmt = static_cast<GotoStmt*>(stmt);
            std::cout << "[GotoStmt]" << std::endl;
        } break;

        case StmtKind::IfStmt: {
            IfStmt* ifStmt = static_cast<IfStmt*>(stmt);
            std::cout << "[IfStmt]" << std::endl;
        } break;

        case StmtKind::LabelStmt: {
            LabelStmt* labelStmt = static_cast<LabelStmt*>(stmt);
            std::cout << "[LabelStmt]" << std::endl;
        } break;

        case StmtKind::ReturnStmt: {
            std::cout << "[ReturnStmt]" << std::endl;
        } break;

        case StmtKind::SwitchStmt: {
            SwitchStmt* switchStmt = static_cast<SwitchStmt*>(stmt);
            std::cout << "[SwitchStmt]" << std::endl;
        } break;

        case StmtKind::UseStmt: {
            UseStmt* useStmt = static_cast<UseStmt*>(stmt);
            std::cout << "[UseStmt]" << std::endl;
        } break;

        case StmtKind::WhileStmt: {
            WhileStmt* whileStmt = static_cast<WhileStmt*>(stmt);
            std::cout << "[WhileStmt]" << std::endl;
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
            std::cout << "[ArraySubscriptExpr]" << std::endl;
        } break;

        case ExprKind::BinaryOpExpr: {
            std::cout << "[BinaryOpExpr]" << std::endl;
        } break;

        case ExprKind::CallExpr: {
            std::cout << "[CallExpr]" << std::endl;
        } break;

        case ExprKind::CastExpr: {
            std::cout << "[CastExpr]" << std::endl;
        } break;

        case ExprKind::DeclRefExpr: {
            std::cout << "[DeclRefExpr]" << std::endl;
        } break;

        case ExprKind::InitalizerExpr: {
            std::cout << "[InitalizerExpr]" << std::endl;
        } break;

        case ExprKind::MemberExpr: {
            std::cout << "[MemberExpr]" << std::endl;
        } break;

        case ExprKind::ParenExpr: {
            std::cout << "[ParenExpr]" << std::endl;
        } break;

        case ExprKind::TernaryExpr: {
            std::cout << "[TernaryExpr]" << std::endl;
        } break;

        case ExprKind::UnaryOpExpr: {
            std::cout << "[UnaryOpExpr]" << std::endl;
        } break;

        case ExprKind::BooleanLiteralExpr: {
            std::cout << "[BooleanLiteralExpr]" << std::endl;
        } break;

        case ExprKind::CharLiteralExpr: {
            std::cout << "[CharLiteralExpr]" << std::endl;
        } break;

        case ExprKind::IntegerLiteralExpr: {
            std::cout << "[IntegerLiteralExpr]" << std::endl;
        } break;

        case ExprKind::RealLiteralExpr: {
            std::cout << "[RealLiteralExpr]" << std::endl;
        } break;

        case ExprKind::StringLiteralExpr: {
            std::cout << "[StringLiteralExpr]" << std::endl;
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