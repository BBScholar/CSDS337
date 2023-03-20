#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/Verifier.h>

// clang++ `llvm-config --libs core native` main.cpp -o main
int main() {
    llvm::LLVMContext ctx;
    llvm::Module mod1("sampleUnit", ctx);


    llvm::IRBuilder<> builder(ctx);

    auto* putsFunc = llvm::Function::Create(
        llvm::FunctionType::get(
            builder.getInt32Ty(),
            {builder.getInt8PtrTy()},
            false
        ),
        llvm::GlobalValue::LinkageTypes::ExternalLinkage,
        "puts",
        mod1
    );

    // auto* func = llvm::Function::Create(
    //     llvm::FunctionType::get(
    //         builder.getVoidTy(),
    //         {builder.getInt32Ty(), builder.getFloatTy()},
    //         false
    //     ),
    //     llvm::GlobalValue::LinkageTypes::ExternalLinkage,
    //     "func",
    //     mod1
    // );
    //
    auto* printf = llvm::Function::Create(
        llvm::FunctionType::get(
            builder.getInt32Ty(),
            {builder.getInt8PtrTy()},
            true
        ),
        llvm::GlobalValue::LinkageTypes::ExternalLinkage,
        "printf",
        mod1
    );

    //
    // auto* funcEntry = llvm::BasicBlock::Create(ctx, "entry", func);

    // builder.SetInsertPoint(funcEntry);
    // auto* res = builder.CreateSub(
    //         llvm::ConstantInt::get(builder.getInt32Ty(), 3, true), 
    //         llvm::ConstantInt::get(builder.getInt32Ty(), 5, true)
    // );
    // builder.CreateRetVoid();
    //
    // llvm::verifyFunction(*func);
    auto* fib = llvm::Function::Create(
        llvm::FunctionType::get(
            builder.getInt32Ty(),
            {builder.getInt32Ty()},
            false
        ),
        llvm::GlobalValue::LinkageTypes::ExternalLinkage,
        "fib",
        mod1
    );
    //
    auto* main = llvm::Function::Create(
        llvm::FunctionType::get(
            builder.getInt32Ty(),
            {},
            false
        ),
        llvm::GlobalValue::LinkageTypes::ExternalLinkage,
        "main",
        mod1
    );

    auto* mainEntry = llvm::BasicBlock::Create(ctx, "entry", main);
    builder.SetInsertPoint(mainEntry);
    builder.CreateCall(
        putsFunc,
        { builder.CreateGlobalStringPtr("Hello World\n") }
    );
    builder.CreateCall(
        printf, 
        { builder.CreateGlobalStringPtr("Bruh moment: %d\n"), llvm::ConstantInt::get(builder.getInt32Ty(), 42, true)}
    ); 
    builder.CreateRet(llvm::ConstantInt::get(builder.getInt32Ty(), 0, false));
    
    llvm::raw_fd_ostream out(0, false);
    llvm::verifyFunction(*main, &out);

    std::error_code err;
    llvm::raw_fd_ostream irOut("sampleUnit.ll", err);
    mod1.print(irOut, nullptr);
    irOut.close();

    llvm::raw_fd_ostream bcOut("sampleUnit.bc", err);
    mod1.print(bcOut, nullptr);
    bcOut.close();

    return 0;
}
