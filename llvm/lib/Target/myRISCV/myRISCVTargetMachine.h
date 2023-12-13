#ifndef LLVM_LIB_TARGET_myRISCV_myRISCVTARGETMACHINE_H
#define LLVM_LIB_TARGET_myRISCV_myRISCVTARGETMACHINE_H

#include "myRISCVInstrInfo.h"
#include "myRISCVSubtarget.h"
#include "llvm/Target/TargetMachine.h"
#include <optional>

namespace llvm{

class Module;
class myRISCVTargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF; // for code emission phase
  mutable StringMap<std::unique_ptr<myRISCVSubtarget>> SubtargetMap;

public:
  myRISCVTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     std::optional<Reloc::Model> RM,
                     std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                     bool JIT);
  ~myRISCVTargetMachine() override;

  const myRISCVSubtarget *getSubtargetImpl(const Function &F) const override;

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }

  MachineFunctionInfo *
  createMachineFunctionInfo(BumpPtrAllocator &Allocator, const Function &F,
                            const TargetSubtargetInfo *STI) const override;
};
}// end namespace llvm
