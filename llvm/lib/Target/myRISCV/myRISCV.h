#ifndef LLVM_LIB_TARGET_MYRISCV_MYRISCV_H
#define LLVM_LIB_TARGET_MYRISCV_MYRISCV_H

#include "llvm/Target/TargetMachine.h"

namespace llvm {
class myRISCVTargetMachine : public TargetMachine {
public:
  myRISCVTargetMachine(const Target &T, const StringRef DataLayoutString,
                       const Triple &TargetTriple, StringRef CPU, StringRef FS,
                       const TargetOptions &Options)
    : TargetMachine(T, DataLayoutString, TargetTriple, CPU, FS, Options) {}
    
};
} // End namespace llvm

#endif
