#ifndef LLVM_LIB_TARGET_MYRISCV_MYRISCV_H
#define LLVM_LIB_TARGET_MYRISCV_MYRISCV_H

#include "llvm/Target/TargetMachine.h"

namespace llvm {
class FunctionPass;
class myRISCVTargetMachine;

FunctionPass *createmyRISCVISelDAG(myRISCVTargetMachine &TM,
                                   CodeGenOptLevel OptLevel);
} // End namespace llvm

#endif
