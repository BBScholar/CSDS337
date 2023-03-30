#include "for.h"

#include "../function.h"

std::unique_ptr<VarType> ASTStatementFor::StatementReturnType(ASTFunction& func) {
    return nullptr;
}

void ASTStatementFor::Compile(llvm::Module& mod, llvm::IRBuilder<>& builder, ASTFunction& func) {

    /*
        forLoop 
    
    */

    auto* funcVal = (llvm::Function*) func.GetVariableValue(func.name);

    auto* forLoop = llvm::BasicBlock::Create(builder.getContext(), "forLoop", funcVal);
    auto* forLoopBody = llvm::BasicBlock::Create(builder.getContext(), "forLoopBody", funcVal);
    auto* forLoopEnd = llvm::BasicBlock::Create(builder.getContext(), "forLoopEnd", funcVal);

    before->Compile(builder, func);
    builder.CreateBr(forLoop);

    builder.SetInsertPoint(forLoop);
    auto* cond = condition->CompileRValue(builder, func);
    builder.CreateCondBr(cond, forLoopBody, forLoopEnd);

    builder.SetInsertPoint(forLoopBody);
    then->Compile(mod, builder, func); 
    after->Compile(builder, func);
    builder.CreateBr(forLoop);

    builder.SetInsertPoint(forLoopEnd);
}

std::string ASTStatementFor::ToString(const std::string& prefix)
{
    std::string output = "for\n";
    output += prefix + "├──" + before->ToString(prefix + "│  ");
    output += prefix + "├──" + condition->ToString(prefix + "   ");
    output += prefix + "└──" + after->ToString(prefix + "   ");
    output += prefix + "└──" + then->ToString(prefix + "   ");
    return output;
}