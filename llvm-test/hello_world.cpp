#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>

int main() {
  llvm::LLVMContext ctx;
  llvm::Module mod("sampleUnit", ctx);
  llvm::IRBuilder<> builder(ctx);

  llvm::Function *putsFunc = llvm::Function::Create(
						    llvm::FunctionType::get(
									    llvm::Type::getInt32Ty(ctx),
									    { llvm::Type::getInt8PtrTy(ctx) },
									    false
									    ),
						    llvm::GlobalValue::LinkageTypes::ExternalLinkage,
						    "puts",
						    mod
						    );

  llvm::Function *func = llvm::Function::Create(
						llvm::FunctionType::get(
									llvm::Type::getInt32Ty(ctx),
									{},
									false
									),
						llvm::GlobalValue::LinkageTypes::ExternalLinkage,
						"main",
						mod
						);

  llvm::BasicBlock *funcEntry = llvm::BasicBlock::Create(ctx, "entry", func);
  builder.SetInsertPoint(funcEntry);
  builder.CreateCall(putsFunc, { builder.CreateGlobalStringPtr("Hello World!\n")});
  builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(ctx), 0));
  
  llvm::verifyFunction(*func);
  
  std::error_code err;
  llvm::raw_fd_ostream irOut("sampleUnit.ll", err);
  mod.print(irOut, nullptr);
  irOut.close();

  llvm::raw_fd_ostream bcOut("sampleUnit.bc", err);
  mod.print(bcOut, nullptr);
  bcOut.close();

  return 0;
}
