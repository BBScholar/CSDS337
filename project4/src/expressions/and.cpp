#include "and.h"

#include "../function.h"

std::unique_ptr<VarType> ASTExpressionAnd::ReturnType(ASTFunction& func)
{
    return VarTypeSimple::BoolType.Copy(); // a || b is always a boolean.
}

bool ASTExpressionAnd::IsLValue(ASTFunction& func)
{
    return false; // || operator works on two R-Values to produce an R-Value.
}

llvm::Value* ASTExpressionAnd::Compile(llvm::IRBuilder<>& builder, ASTFunction& func) // Hm, this isn't the most efficient approach. I can think of a much easier way...
{

    // // Make sure to cast both sides as booleans first.
    ASTExpression::ImplicitCast(func, left, &VarTypeSimple::BoolType);
    ASTExpression::ImplicitCast(func, right, &VarTypeSimple::BoolType);

    // // Create blocks. Check right is if left is false, and we need to check the right one too. Continue block happens if true.
    auto* funcVal = (llvm::Function*)func.GetVariableValue(func.name);

    // create blocks
    auto* falseBlock = llvm::BasicBlock::Create(builder.getContext(), "andFalse", funcVal);
    auto* trueBlock = llvm::BasicBlock::Create(builder.getContext(), "andTrue", funcVal);
    auto* cont = llvm::BasicBlock::Create(builder.getContext(), "cont", funcVal);

    // check left value
    auto* leftVal = left->CompileRValue(builder, func);
    builder.CreateCondBr(leftVal, trueBlock, falseBlock);

    // check right value if left value is true
    builder.SetInsertPoint(trueBlock);
    auto* rightVal= right->CompileRValue(builder, func);
    builder.CreateBr(cont);


    builder.SetInsertPoint(falseBlock);
    builder.CreateBr(cont);

    // // Tell LLVM that it should either select the left value or the right one depending on where we came from.
    builder.SetInsertPoint(cont);
    auto* res = builder.CreatePHI(VarTypeSimple::BoolType.GetLLVMType(builder.getContext()), 2);
    res->addIncoming(rightVal, trueBlock); // when both are true, return left value because it'll be a true
    res->addIncoming(leftVal, falseBlock); // when in false block

    return res;

    // neither of these work
    // return builder.CreateLogicalAnd(left->CompileRValue(builder, func), right->CompileRValue(builder, func));

    // auto* leftVal = left->CompileRValue(builder, func);
    // return builder.CreateSelect(leftVal, right->CompileRValue(builder, func), leftVal);
}

std::string ASTExpressionAnd::ToString(const std::string& prefix)
{
    std::string ret = "(&&)\n";
    ret += prefix + "├──" + left->ToString(prefix + "│  ");
    ret += prefix + "└──" + right->ToString(prefix + "   ");
    return ret;
}