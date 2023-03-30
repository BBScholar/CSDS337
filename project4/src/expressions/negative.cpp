#include "negative.h"


std::unique_ptr<VarType> ASTExpressionNegation::ReturnType(ASTFunction& func) {
    return expr->ReturnType(func)->Copy();
}

bool ASTExpressionNegation::IsLValue(ASTFunction& func) {
    return false;
}

llvm::Value* ASTExpressionNegation::Compile(llvm::IRBuilder<>& builder, ASTFunction& func) {
    auto* value = expr->Compile(builder, func);

    auto retType = ReturnType(func); 
    if(retType->Equals(&VarTypeSimple::IntType)) {
        return builder.CreateNeg(value);
    } else if(retType->Equals(&VarTypeSimple::FloatType)) {
        return builder.CreateFNeg(value);
    } else {
        throw std::runtime_error("ERROR: Can not perform negation. Input must be integer or float type.");
    }
}

std::string ASTExpressionNegation::ToString(const std::string& prefix) {
    std::string ret = "negate\n";
    ret += prefix + "├──" + expr->ToString(prefix + "│  ");
    return ret;
}