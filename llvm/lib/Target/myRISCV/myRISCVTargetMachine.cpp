#include "myRISCVTargetMachine.h"
#include "TargetInfo/myRISCVTargetInfo.h"
#include "myRISCV.h"
#include "myRISCVISelDAGToDAG.h"
#include "myRISCVSubtarget.h"
#include "myRISCVTargetObjectFile.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Target/TargetLoweringObjectFile.h"

using namespace llvm;

static StringRef computeDataLayout(const Triple &TT,
                                   const TargetOptions &Options) {
  if (TT.isArch64Bit()) {
    return "e-m:m-p:64:64-i8:8:32-i16:16:32-i64:64-n64-S128";
  } else {
    assert(TT.isArch32Bit() && "myRISCV must be 32bit or 64bit architecture");
    return "e-m:m-p:32:32-i8:8:32-i16:16:32-i64:64-n32-S64";
  }
}

static Reloc::Model getEffectiveRelocModel(const Triple &TT,
                                           std::optional<Reloc::Model> RM) {
  return RM.value_or(Reloc::Static);
}

myRISCVTargetMachine::myRISCVTargetMachine(const Target &T, const Triple &TT,
                                           StringRef CPU, StringRef FS,
                                           const TargetOptions &Options,
                                           std::optional<Reloc::Model> RM,
                                           std::optional<CodeModel::Model> CM,
                                           CodeGenOptLevel OL, bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(TT, Options), TT, CPU, FS, Options,
                        getEffectiveRelocModel(TT, RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<myRISCVTargetObjectFile>()),
      DefaultSubtarget(TT, CPU, CPU, FS, *this) {
  initAsmInfo(); // initialization for asminfo, it will cause error in execution
                 // time if you don't initial it.
}

myRISCVTargetMachine::~myRISCVTargetMachine() {}

class myRISCVPassConfig : public TargetPassConfig {
public:
  myRISCVPassConfig(myRISCVTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  bool addInstSelector() override {
    addPass(createmyRISCVISelDAG(getTM<myRISCVTargetMachine>(), getOptLevel()));
    return false;
  }
};

TargetPassConfig *myRISCVTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new myRISCVPassConfig(*this, PM);
}

const myRISCVSubtarget *
myRISCVTargetMachine::getSubtargetImpl(const Function &F) const {
  return &DefaultSubtarget;
}

TargetLoweringObjectFile *myRISCVTargetMachine::getObjFileLowering() const {
  return TLOF.get();
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializemyRISCVTarget() {
  RegisterTargetMachine<myRISCVTargetMachine> X(getmyRISCVTarget());
}
