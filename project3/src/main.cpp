#include <iostream>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>

// Starter code for the assignment.
int main()
{
    
    // for outputing verifications
    llvm::raw_fd_ostream out(0, false);

    // Step 1 - Setup LLVM module. Note exporting is continued below.
    llvm::LLVMContext context;              // Our base context. This is how we talk to LLVM.
    llvm::Module sampleMod {"sampleMod", context};
    
    // Step 2 - 
    llvm::IRBuilder<> builder (context);

    auto* simple = llvm::Function::Create(llvm::FunctionType::get(builder.getInt32Ty(), {}, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "simple", &sampleMod);
    {
        auto* simple_entry = llvm::BasicBlock::Create(context, "entry", simple);
        builder.SetInsertPoint(simple_entry);
        builder.CreateRet(llvm::ConstantInt::get(builder.getInt32Ty(), 0));
    }

    llvm::verifyFunction(*simple, &out);

    // Step 3 - 
    auto* add = llvm::Function::Create(llvm::FunctionType::get(builder.getInt32Ty(), {builder.getInt32Ty(), builder.getInt32Ty()}, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "add", &sampleMod);
    {
        auto* add_entry = llvm::BasicBlock::Create(context, "entry", add);
        builder.SetInsertPoint(add_entry);
        builder.CreateRet(builder.CreateAdd(add->getArg(0), add->getArg(1)));
    }
    llvm::verifyFunction(*add, &out);


        // step 4 - 
    auto* addIntFloat = llvm::Function::Create(llvm::FunctionType::get(builder.getFloatTy(), {builder.getInt32Ty(), builder.getFloatTy()}, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "addIntFloat", &sampleMod);
    {
        auto* addIntFloat_entry = llvm::BasicBlock::Create(context, "entry", addIntFloat);
        builder.SetInsertPoint(addIntFloat_entry);
        // TODO: Check how casting works, might be wrong kind of cast
        builder.CreateRet(builder.CreateFAdd(builder.CreateSIToFP(addIntFloat->getArg(0), builder.getFloatTy()), addIntFloat->getArg(1)));
    }
    llvm::verifyFunction(*addIntFloat, &out);

    // step 5 - 
    auto* conditional = llvm::Function::Create(llvm::FunctionType::get(builder.getInt32Ty(), {builder.getInt1Ty()}, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "conditional", &sampleMod);
    {
        auto* conditional_entry = llvm::BasicBlock::Create(context, "entry", conditional);
        builder.SetInsertPoint(conditional_entry);
        
        // allocate stack variable
        auto* p = builder.CreateAlloca(builder.getInt32Ty());

        // create labels 
        auto* if_true = llvm::BasicBlock::Create(context, "if_true", conditional);
        auto* if_false = llvm::BasicBlock::Create(context, "if_false", conditional);
        auto* after = llvm::BasicBlock::Create(context, "after", conditional);
        
        builder.CreateCondBr(conditional->getArg(0), if_true, if_false);
        
        builder.SetInsertPoint(if_true);
        builder.CreateStore(llvm::ConstantInt::get(builder.getInt32Ty(), 3, true), p);
        builder.CreateBr(after);
        
        builder.SetInsertPoint(if_false);
        builder.CreateStore(llvm::ConstantInt::get(builder.getInt32Ty(), 5, true), p);
        builder.CreateBr(after);
        
        builder.SetInsertPoint(after);
        // end of block 
        //
        auto* load = builder.CreateLoad(builder.getInt32Ty(), p);
        
        builder.CreateRet(builder.CreateAdd(load, llvm::ConstantInt::get(builder.getInt32Ty(), 11, true)));
    }
    llvm::verifyFunction(*conditional, &out);
    
    // step 6
    auto* oneTwoPhi = llvm::Function::Create(llvm::FunctionType::get(builder.getInt32Ty(), {builder.getInt1Ty()}, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "oneTwoPhi", &sampleMod); 
    {
        auto* oneTwoPhi_entry = llvm::BasicBlock::Create(context, "entry", oneTwoPhi);
        builder.SetInsertPoint(oneTwoPhi_entry);
        
        auto* if_true = llvm::BasicBlock::Create(context, "if_true", oneTwoPhi);
        auto* if_false = llvm::BasicBlock::Create(context, "if_false", oneTwoPhi);
        auto* after = llvm::BasicBlock::Create(context, "after", oneTwoPhi);

        builder.CreateCondBr(oneTwoPhi->getArg(0), if_true, if_false);
        
        builder.SetInsertPoint(if_true);
        builder.CreateBr(after);

        builder.SetInsertPoint(if_false);
        builder.CreateBr(after);

        builder.SetInsertPoint(after);
        auto* phi = builder.CreatePHI(builder.getInt32Ty(), 2);
        phi->addIncoming(llvm::ConstantInt::get(builder.getInt32Ty(), 3, true), if_true);
        phi->addIncoming(llvm::ConstantInt::get(builder.getInt32Ty(), 5, true), if_false);

        builder.CreateRet(builder.CreateAdd(phi, llvm::ConstantInt::get(builder.getInt32Ty(), 11, true)));
    }
    llvm::verifyFunction(*oneTwoPhi, &out);
     

    // step 7
    auto* selection = llvm::Function::Create(llvm::FunctionType::get(builder.getInt32Ty(), {builder.getInt1Ty()}, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "selection", &sampleMod); 
    {
        auto* selection_entry = llvm::BasicBlock::Create(context, "entry", selection);
        builder.SetInsertPoint(selection_entry);

        auto* select = builder.CreateSelect(selection->getArg(0), llvm::ConstantInt::get(builder.getInt32Ty(), 3, false), llvm::ConstantInt::get(builder.getInt32Ty(), 5, false));

        builder.CreateRet(builder.CreateAdd(select, llvm::ConstantInt::get(builder.getInt32Ty(), 11, true)));
    }
    llvm::verifyFunction(*selection, &out);

    // optional stuff 
    auto* malloc = llvm::Function::Create(llvm::FunctionType::get(builder.getPtrTy(), {builder.getInt32Ty()}, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "malloc", &sampleMod);
    auto* free = llvm::Function::Create(llvm::FunctionType::get(builder.getVoidTy(), {builder.getPtrTy()}, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "free", &sampleMod);
    // auto* printf  = llvm::Function::Create(llvm::FunctionType::get(builder.getVoidTy(), {}))

    // heap test 
    auto* heap_test = llvm::Function::Create(llvm::FunctionType::get(builder.getVoidTy(), {}, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "heapTest", &sampleMod);
    {
        auto* entry = llvm::BasicBlock::Create(context, "entry", heap_test);
        builder.SetInsertPoint(entry);
        
        auto* size = llvm::ConstantInt::get(builder.getInt32Ty(), 32, false);
        auto* mem = builder.CreateCall(malloc->getFunctionType(), malloc, {size});

        builder.CreateStore(size, mem);

        builder.CreateCall(free->getFunctionType(), free, {mem});
        builder.CreateRetVoid();
    }
    llvm::verifyFunction(*heap_test, &out);
    
    llvm::verifyModule(sampleMod, &out);

    // Step 1 - Export LLVM module.
    std::error_code err;                             // Error code from outstream, we can reuse this.
    llvm::raw_fd_ostream outLl("sampleMod.ll", err); // Open an output file.
    sampleMod.print(outLl, nullptr);                       // Print LLVM assembly to the file.
    outLl.close();                                   // Close file to save resources.S
                                                     //
    llvm::raw_fd_ostream outBc("sampleMod.bc", err);
    llvm::WriteBitcodeToFile(sampleMod, outBc);
    outBc.close();
    
#define RUN_OPT
#ifdef RUN_OPT 
    // step 8
    auto pass_manager = llvm::legacy::FunctionPassManager(&sampleMod);
    
    // add passes
    pass_manager.add(llvm::createPromoteMemoryToRegisterPass());
    pass_manager.add(llvm::createReassociatePass());
    pass_manager.add(llvm::createGVNPass());
    pass_manager.add(llvm::createCFGSimplificationPass());
    
    // add functions to optimize
    pass_manager.run(*simple);
    pass_manager.run(*add);
    pass_manager.run(*addIntFloat);
    pass_manager.run(*conditional);
    pass_manager.run(*oneTwoPhi);
    pass_manager.run(*selection);

    // output optimized functions to their own files
    // for ease of comparison
    llvm::raw_fd_ostream outLl_opt("sampleMod_opt.ll", err); // Open an output file.
    sampleMod.print(outLl_opt, nullptr);                       // Print LLVM assembly to the file.
    outLl_opt.close();                                   // Close file to save resources.S
                                                     //
    llvm::raw_fd_ostream outBc_opt("sampleMod_opt.bc", err);
    llvm::WriteBitcodeToFile(sampleMod, outBc_opt);
    outBc_opt.close();
#endif

    // README
    // Step 8 writeup:
    // Functions simple, add, and addIntFloat all remain the same after the optimization 
    // passes. I'd assume that this is because these functions are extremely simple and can't 
    // be optimized any more with the currently selected passes.
    // The optimization passes simplify the conditional, oneTwoPhi,
    // and selection methods into identical LLVM IR. After optimization 
    // all 3 functions consist of a select statement, add statement, and the return.
    // The optimization also gets rid of the stack allocation in the conditional function/
    // This is replaced with a register in the optimized function.
    // For some reason, the optimized version of the select function 
    // uses %1 instead of %. . Not sure what the difference is.



    return 0;
}
