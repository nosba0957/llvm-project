#include "TargetInfo/myRISCVTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getmyRISCVTarget() {
  static Target myRISCVTargetInfo;
  return myRISCVTargetInfo;
}

extern "C" void LLVMInitialmyRISCVTargetInfo() {
  RegisterTarget<Triple::myRISCV, /*HasJIT=*/false> X(
    getmyRISCVTarget(), "myriscv", "myriscv", "myRISCV");
}
