#include "TargetInfo/myRISCVTargetInfo.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getmyRISCVTarget() {
  static Target myRISCVTargetInfo;
  return myRISCVTargetInfo;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializemyRISCVTargetInfo() {
  RegisterTarget<Triple::myriscv, /*HasJIT=*/false> X(
      getmyRISCVTarget(), "myriscv", "myriscv", "myRISCV");
}
