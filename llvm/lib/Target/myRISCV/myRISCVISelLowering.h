#ifndef LLVM_LIB_TARGET_MYRISCV_MYRISCVISELLOWERING_H
#define LLVM_LIB_TARGET_MYRISCV_MYRISCVISELLOWERING_H

#include "llvm/CodeGen/TargetLowering.h"
#include "myRISCVTargetMachine.h"

namespace llvm {
class myRSICVTargetLowering : public TargetLowering {
public:

  myRISCVTargetLowering(TargetMachine &TM);


};
} // End namespace llvm

#endif
