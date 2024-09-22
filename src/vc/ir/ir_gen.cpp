#include <vc/ir/ir_gen.h>
#include <vc/ast/declgroup.h>
#include <vc/ast/decl.h>
#include <vc/ast/stmt.h>
#include <vc/ast/expr.h>
#include <vc/ast/type.h>
namespace vc {

ir_module IRGen::generateModule(ModuleDecl* decl) {
    ir_module result;

    return result;
}

void IRGen::generateDeclGroup(DeclGroup* declGroup) {
    for (int i = 0; i < declGroup->entries.size(); i++) {
        Decl* decl = declGroup->entries[i];
        generateDecl(decl);
    }
}

void IRGen::generateDecl(Decl* decl) {
    switch (decl->declKind) {
        case DeclKind::EnumConstDecl: {
            EnumConstDecl* enumConstDecl = static_cast<EnumConstDecl*>(decl);
        } break;

        case DeclKind::EnumDecl: {
            EnumDecl* enumDecl = static_cast<EnumDecl*>(decl);
        } break;

        case DeclKind::FunctionArgDecl: {
            FunctionArgDecl* functionArgDecl = static_cast<FunctionArgDecl*>(decl);
        } break;

        case DeclKind::FunctionDecl: {
            FunctionDecl* functionDecl = static_cast<FunctionDecl*>(decl);
        } break;

        case DeclKind::ImportDecl: {
            ImportDecl* importDecl = static_cast<ImportDecl*>(decl);
        } break;

        case DeclKind::ModuleDecl: {
            ModuleDecl* moduleDecl = static_cast<ModuleDecl*>(decl);
        } break;

        case DeclKind::NamespaceDecl: {
            NamespaceDecl* namespaceDecl = static_cast<NamespaceDecl*>(decl);
        } break;

        case DeclKind::PackageDecl: {
            PackageDecl* packageDecl = static_cast<PackageDecl*>(decl);
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
        } break;

        case DeclKind::TypedefDecl: {
            TypedefDecl* typedefDecl = static_cast<TypedefDecl*>(decl);
        } break;

        case DeclKind::UsingDecl: {
            UsingDecl* usingDecl = static_cast<UsingDecl*>(decl);
        } break;

        case DeclKind::VarDecl: {
            VarDecl* varDecl = static_cast<VarDecl*>(decl);

        } break;

        default:
        // something something unhandled declaration kind in ir generation
        break;
    }
}

void IRGen::generateStmt(Stmt* stmt) {
    switch (stmt->stmtKind) {

        case StmtKind::BreakStmt: {
            std::cout << "[BreakStmt]" << std::endl;
        } break;

        case StmtKind::CaseStmt: {
            CaseStmt* caseStmt = static_cast<CaseStmt*>(stmt);
        } break;

        case StmtKind::CompoundStmt: {
            CompoundStmt* compoundStmt = static_cast<CompoundStmt*>(stmt);
        } break;

        case StmtKind::ContinueStmt: {
        } break;

        case StmtKind::DeclStmt: {
            DeclStmt* declStmt = static_cast<DeclStmt*>(stmt);
        } break;

        case StmtKind::DefaultStmt: {
            DefaultStmt* defaultStmt = static_cast<DefaultStmt*>(stmt);
        } break;

        case StmtKind::DeferStmt: {
            DeferStmt* deferStmt = static_cast<DeferStmt*>(stmt);
        } break;

        case StmtKind::DoStmt: {
            DoStmt* doStmt = static_cast<DoStmt*>(stmt);
        } break;

        case StmtKind::ExprStmt: {
            Expr* exprStmt = static_cast<Expr*>(stmt);
        } break;

        case StmtKind::ForStmt: {
            ForStmt* forStmt = static_cast<ForStmt*>(stmt);
        } break;

        case StmtKind::GotoStmt: {
            GotoStmt* gotoStmt = static_cast<GotoStmt*>(stmt);
        } break;

        case StmtKind::IfStmt: {
            IfStmt* ifStmt = static_cast<IfStmt*>(stmt);
        } break;

        case StmtKind::LabelStmt: {
            LabelStmt* labelStmt = static_cast<LabelStmt*>(stmt);
        } break;

        case StmtKind::ReturnStmt: {
        } break;

        case StmtKind::SwitchStmt: {
            SwitchStmt* switchStmt = static_cast<SwitchStmt*>(stmt);
        } break;

        case StmtKind::UseStmt: {
            UseStmt* useStmt = static_cast<UseStmt*>(stmt);
        } break;

        case StmtKind::WhileStmt: {
            WhileStmt* whileStmt = static_cast<WhileStmt*>(stmt);
        } break;

        default:
        // something something unhandled statement kind in ir generation
        break;
    }
}

void IRGen::generateExpr(Expr* expr) {
    switch (expr->exprKind) {
        case ExprKind::ArraySubscriptExpr: {
            ArraySubscriptExpr* arraySubscriptExpr = static_cast<ArraySubscriptExpr*>(expr);
        } break;

        case ExprKind::BinaryOpExpr: {
            BinaryOpExpr* binaryOpExpr = static_cast<BinaryOpExpr*>(expr);
        } break;

        case ExprKind::CallExpr: {
            CallExpr* callExpr = static_cast<CallExpr*>(expr);
        } break;

        case ExprKind::CastExpr: {
            CastExpr* castExpr = static_cast<CastExpr*>(expr);
        } break;

        case ExprKind::DeclRefExpr: {
            DeclRefExpr* declRefExpr = static_cast<DeclRefExpr*>(expr);
        } break;

        case ExprKind::InitalizerExpr: {
            InitalizerExpr* initalizerExpr = static_cast<InitalizerExpr*>(expr);
        } break;

        case ExprKind::MemberExpr: {
            MemberExpr* memberExpr = static_cast<MemberExpr*>(expr);
        } break;

        case ExprKind::ParenExpr: {
            ParenExpr* parenExpr = static_cast<ParenExpr*>(expr);
        } break;

        case ExprKind::TernaryExpr: {
            TernaryExpr* ternaryExpr = static_cast<TernaryExpr*>(expr);
        } break;

        case ExprKind::UnaryOpExpr: {
            UnaryOpExpr* unaryOpExpr = static_cast<UnaryOpExpr*>(expr);
        } break;

        case ExprKind::BooleanLiteralExpr: {
            BooleanLiteralExpr* booleanLiteralExpr = static_cast<BooleanLiteralExpr*>(expr);
        } break;

        case ExprKind::CharLiteralExpr: {
            CharLiteralExpr* charLiteralExpr = static_cast<CharLiteralExpr*>(expr);
        } break;

        case ExprKind::IntegerLiteralExpr: {
            IntegerLiteralExpr* integerLiteralExpr = static_cast<IntegerLiteralExpr*>(expr);
        } break;

        case ExprKind::RealLiteralExpr: {
            RealLiteralExpr* realLiteralExpr = static_cast<RealLiteralExpr*>(expr);
        } break;

        case ExprKind::StringLiteralExpr: {
            StringLiteralExpr* stringLiteralExpr = static_cast<StringLiteralExpr*>(expr);
        } break;

        default:
        // something something unhandled expression kind in ir generation
        break;
    }
}

void IRGen::generateType(Type* type) {
    switch (type->typeKind) {

        case TypeKind::ArrayType: {
            ArrayType* arrayType = static_cast<ArrayType*>(type);
        } break;

        case TypeKind::BuiltinType: {
            BuiltinType* builtinType = static_cast<BuiltinType*>(type);
        } break;

        case TypeKind::DeclRefType: {
            DeclRefType* declRefType = static_cast<DeclRefType*>(type);
        } break;

        case TypeKind::PointerType: {
            PointerType* pointerType = static_cast<PointerType*>(type);
        } break;

        default:
        // something something unhandled type kind in ir generation
        break;
    }
}
}