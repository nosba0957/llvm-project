#ifndef LLVM_LIB_TARGET_MYRISCV_MYRISCVTARGETOBJECTFILE_H
#define LLVM_LIB_TARGET_MYRISCV_MYRISCVTARGETOBJECTFILE_H

#include "myRISCVTargetMachine.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"

namespace llvm {

class myRISCVTargetMachine;

class myRISCVTargetObjectFile : public TargetLoweringObjectFileELF {
  const myRISCVTargetMachine *TM;

public:
  void Initialize(MCContext &Ctx, const TargetMachine &TM) override;
};
} // namespace llvm

#endif
