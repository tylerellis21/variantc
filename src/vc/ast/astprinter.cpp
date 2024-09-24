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
            if (functionDecl->namedReturnDecl) {
                printDecl(functionDecl->namedReturnDecl, indent + 1);
            }
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
            printExpr(caseStmt->valueExpr, indent + 1);
            printStmt(caseStmt->bodyStmt, indent + 1);
        } break;

        case StmtKind::CompoundStmt: {
            CompoundStmt* compoundStmt = static_cast<CompoundStmt*>(stmt);
            std::cout << "[CompoundStmt]" << std::endl;
            for (int i = 0; i < compoundStmt->statements.size(); i++) {
                Stmt* subStmt = compoundStmt->statements[i];
                printStmt(subStmt, indent + 1);
            }
        } break;

        case StmtKind::ContinueStmt: {
            std::cout << "[ContinueStmt]" << std::endl;
        } break;

        case StmtKind::DeclStmt: {
            DeclStmt* declStmt = static_cast<DeclStmt*>(stmt);
            std::cout << "[DeclStmt]" << std::endl;
            printDeclGroup(declStmt->declGroup, indent + 1);
        } break;

        case StmtKind::DefaultStmt: {
            DefaultStmt* defaultStmt = static_cast<DefaultStmt*>(stmt);
            std::cout << "[DefaultStmt]" << std::endl;
        } break;

        case StmtKind::DeferStmt: {
            DeferStmt* deferStmt = static_cast<DeferStmt*>(stmt);
            std::cout << "[DeferStmt]" << std::endl;
            printStmt(deferStmt->bodyStmt, indent + 1);
        } break;

        case StmtKind::DoStmt: {
            DoStmt* doStmt = static_cast<DoStmt*>(stmt);
            std::cout << "[DoStmt]" << std::endl;
            printStmt(doStmt->bodyStmt, indent + 1);
            printStmt(doStmt->WhileStmt, indent + 1);
        } break;

        case StmtKind::ExprStmt: {
            Expr* exprStmt = static_cast<Expr*>(stmt);
            std::cout << "[ExprStmt]" << std::endl;
            printExpr(exprStmt, indent + 1);
        } break;

        case StmtKind::ForStmt: {
            ForStmt* forStmt = static_cast<ForStmt*>(stmt);
            std::cout << "[ForStmt]" << std::endl;
            printExpr(forStmt->initExpr, indent + 1);
            printExpr(forStmt->conditionExpr, indent + 1);
            printExpr(forStmt->incrementExpr, indent + 1);
            printStmt(forStmt->bodyStmt, indent + 1);
        } break;

        case StmtKind::GotoStmt: {
            GotoStmt* gotoStmt = static_cast<GotoStmt*>(stmt);
            std::cout << "[GotoStmt] '" << gotoStmt->name << "'" << std::endl;
        } break;

        case StmtKind::IfStmt: {
            IfStmt* ifStmt = static_cast<IfStmt*>(stmt);
            std::cout << "[IfStmt]" << std::endl;
            printExpr(ifStmt->conditionExpr, indent + 1);
            printStmt(ifStmt->bodyStmt, indent + 1);
            if (ifStmt->elseStmt) {
                printStmt(ifStmt->elseStmt, indent + 1);
            }
        } break;

        case StmtKind::LabelStmt: {
            LabelStmt* labelStmt = static_cast<LabelStmt*>(stmt);
            std::cout << "[LabelStmt] '" << labelStmt->name << "'" << std::endl;
        } break;

        case StmtKind::ReturnStmt: {
            std::cout << "[ReturnStmt]" << std::endl;
        } break;

        case StmtKind::SwitchStmt: {
            SwitchStmt* switchStmt = static_cast<SwitchStmt*>(stmt);
            std::cout << "[SwitchStmt]" << std::endl;
            printExpr(switchStmt->conditionExpr, indent + 1);
            printStmt(switchStmt->bodyStmt, indent + 1);
        } break;

        case StmtKind::UseStmt: {
            UseStmt* useStmt = static_cast<UseStmt*>(stmt);
            std::cout << "[UseStmt]" << std::endl;
            printExpr(useStmt->expr, indent + 1);
        } break;

        case StmtKind::WhileStmt: {
            WhileStmt* whileStmt = static_cast<WhileStmt*>(stmt);
            std::cout << "[WhileStmt]" << std::endl;
            printExpr(whileStmt->conditionExpr, indent + 1);
            printStmt(whileStmt->bodyStmt, indent + 1);
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
            ArraySubscriptExpr* arraySubscriptExpr = static_cast<ArraySubscriptExpr*>(expr);
            std::cout << "[ArraySubscriptExpr]" << std::endl;
            printExpr(arraySubscriptExpr->lhs, indent + 1);
            printExpr(arraySubscriptExpr->rhs, indent + 1);
        } break;

        case ExprKind::BinaryOpExpr: {
            BinaryOpExpr* binaryOpExpr = static_cast<BinaryOpExpr*>(expr);
            std::cout << "[BinaryOpExpr] " << toSymbol(binaryOpExpr->op) << std::endl;
            printExpr(binaryOpExpr->lhs, indent + 1);
            printExpr(binaryOpExpr->rhs, indent + 1);
        } break;

        case ExprKind::CallExpr: {
            CallExpr* callExpr = static_cast<CallExpr*>(expr);
            std::cout << "[CallExpr] '" << callExpr->name << "'" << std::endl;
            for (int i = 0; i < callExpr->args.size(); i++) {
                Expr* argument = callExpr->args[i];
                printExpr(argument, indent + 1);
            }
        } break;

        case ExprKind::CastExpr: {
            CastExpr* castExpr = static_cast<CastExpr*>(expr);
            std::cout << "[CastExpr]" << std::endl;
            printType(castExpr->type);
            std::cout << std::endl;
            printExpr(castExpr->expr, indent + 1);
        } break;

        case ExprKind::DeclRefExpr: {
            DeclRefExpr* declRefExpr = static_cast<DeclRefExpr*>(expr);
            std::cout << "[DeclRefExpr] '" << declRefExpr->name << "'" << std::endl;
        } break;

        case ExprKind::InitalizerExpr: {
            InitalizerExpr* initalizerExpr = static_cast<InitalizerExpr*>(expr);
            std::cout << "[InitalizerExpr]" << std::endl;
            for (int i = 0; i < initalizerExpr->values.size(); i++) {
                Expr* subExpr = initalizerExpr->values[i];
                printExpr(subExpr, indent + 1);
            }
        } break;

        case ExprKind::MemberExpr: {
            MemberExpr* memberExpr = static_cast<MemberExpr*>(expr);
            std::cout << "[MemberExpr] '" << memberExpr->name << "'" << std::endl;
        } break;

        case ExprKind::ParenExpr: {
            ParenExpr* parenExpr = static_cast<ParenExpr*>(expr);
            std::cout << "[ParenExpr]" << std::endl;
            printExpr(parenExpr->expr, indent + 1);
        } break;

        case ExprKind::TernaryExpr: {
            TernaryExpr* ternaryExpr = static_cast<TernaryExpr*>(expr);
            std::cout << "[TernaryExpr]" << std::endl;
            printExpr(ternaryExpr->conditionExpr, indent + 1);
            printExpr(ternaryExpr->lhs, indent + 1);
            printExpr(ternaryExpr->rhs, indent + 1);
        } break;

        case ExprKind::UnaryOpExpr: {
            UnaryOpExpr* unaryOpExpr = static_cast<UnaryOpExpr*>(expr);
            std::cout << "[UnaryOpExpr] " << toSymbol(unaryOpExpr->op) << std::endl;
            printExpr(unaryOpExpr->expr, indent + 1);
        } break;

        case ExprKind::BooleanLiteralExpr: {
            BooleanLiteralExpr* booleanLiteralExpr = static_cast<BooleanLiteralExpr*>(expr);
            std::cout << "[BooleanLiteralExpr] " << (booleanLiteralExpr->value ? "true" : "false") << std::endl;
        } break;

        case ExprKind::CharLiteralExpr: {
            CharLiteralExpr* charLiteralExpr = static_cast<CharLiteralExpr*>(expr);
            std::cout << "[CharLiteralExpr] '" << charLiteralExpr->rune_value << "'" << std::endl;
        } break;

        case ExprKind::IntegerLiteralExpr: {
            IntegerLiteralExpr* integerLiteralExpr = static_cast<IntegerLiteralExpr*>(expr);
            if (integerLiteralExpr->builtinKind == BuiltinKind::Int64) {
                std::cout << "[IntegerLiteralExpr] " << integerLiteralExpr->i64_value << std::endl;
            }
            else if (integerLiteralExpr->builtinKind == BuiltinKind::Uint64) {
                std::cout << "[IntegerLiteralExpr] " << integerLiteralExpr->u64_value << std::endl;
            }
            else {
                std::cout << "unhandled integer literal BuiltinKind" << std::endl;
            }
        } break;

        case ExprKind::RealLiteralExpr: {
            RealLiteralExpr* realLiteralExpr = static_cast<RealLiteralExpr*>(expr);
            if (realLiteralExpr->builtinKind == BuiltinKind::Real32) {
                std::cout << "[RealLiteralExpr] " << realLiteralExpr->real32_value << std::endl;
            }
            else if (realLiteralExpr->builtinKind == BuiltinKind::Real64) {
                std::cout << "[RealLiteralExpr] " << realLiteralExpr->real64_value << std::endl;
            }
            else {
                std::cout << "unhandled real literal BuiltinKind" << std::endl;
            }
        } break;

        case ExprKind::StringLiteralExpr: {
            StringLiteralExpr* stringLiteralExpr = static_cast<StringLiteralExpr*>(expr);
            std::cout << "[StringLiteralExpr] '" << stringLiteralExpr->value << "'" << std::endl;
        } break;

        default:
            std::cout << "Unhandled expr kind in ast printer" << std::endl;
        break;
    }
}

void printType(Type* type) {
    switch (type->typeKind) {
        case TypeKind::ArrayType: {
            ArrayType* arrayType = static_cast<ArrayType*>(type);
            printType(arrayType->type);
            std::cout << "[" << arrayType->length << "]";
        } break;

        case TypeKind::BuiltinType: {
            BuiltinType* builtinType = static_cast<BuiltinType*>(type);
            std::cout << builtinKindString(builtinType->builtinKind);
        } break;

        case TypeKind::DeclRefType: {
            DeclRefType* declRefType = static_cast<DeclRefType*>(type);
            std::cout << declRefType->name;
        } break;

        case TypeKind::PointerType: {
            PointerType* pointerType = static_cast<PointerType*>(type);
            printType(pointerType->type);
            std::cout << "*";
        } break;

        default:
            std::cout << "Unhandled type kind in ast printer" << std::endl;
        break;
    }
}

} // namespace vc