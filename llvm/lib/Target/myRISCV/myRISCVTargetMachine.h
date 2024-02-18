#ifndef LLVM_LIB_TARGET_MYRISCV_MYRISCVTARGETMACHINE_H
#define LLVM_LIB_TARGET_MYRISCV_MYRISCVTARGETMACHINE_H

#include "myRISCVInstrInfo.h"
#include "myRISCVSubtarget.h"
#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include "llvm/Target/TargetMachine.h"
#include <memory>
#include <optional>

namespace llvm {
class myRISCVTargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  myRISCVSubtarget DefaultSubtarget;

public:
  // constructor follow the class LLVMTargetMachine
  myRISCVTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                       StringRef FS, const TargetOptions &Options,
                       std::optional<Reloc::Model> RM,
                       std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                       bool JIT);
  ~myRISCVTargetMachine() override;

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  const myRISCVSubtarget *getSubtargetImpl(const Function &F) const override;
  TargetLoweringObjectFile *getObjFileLowering() const override;
};
} // end namespace llvm

#endif
