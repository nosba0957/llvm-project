#include "myRISCVSubtarget.h"
#include "myRISCVFrameLowering.h"
#include "myRISCVRegisterInfo.h"
#include "myRISCVTargetMachine.h"
#include "llvm/Support/raw_ostream.h"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "myRISCVGenSubtargetInfo.inc"

using namespace llvm;

myRISCVSubtarget::myRISCVSubtarget(const Triple &TT, StringRef CPU,
                                   StringRef TuneCPU, StringRef FS,
                                   const myRISCVTargetMachine &TTM)
    : myRISCVGenSubtargetInfo(TT, CPU, TuneCPU, FS), TM(TTM),
      FrameLowering(initializeSubtargetDependencies(TT, CPU, TuneCPU, FS)),
      InstrInfo(), RegInfo(getHwMode()), TLInfo(TM, *this) {}

myRISCVSubtarget::~myRISCVSubtarget() {}

myRISCVSubtarget &myRISCVSubtarget::initializeSubtargetDependencies(
    const Triple &TT, StringRef CPU, StringRef TuneCPU, StringRef FS) {
  // this below will cause error, we should use newest method to handle with
  // CPU.
  /*if (TT.getArch() == Triple::myriscv)
    CPU = "myriscv";
  else {
    errs() << "Architecture " << TargetTriple.getArch()
           << " is not supported for CPU " << CPU << "\n";
    abort();
  }*/
  if (CPU.empty() || CPU == "generic") {
    CPU = "myriscv";
  }

  ParseSubtargetFeatures(CPU, TuneCPU, FS);
  return *this;
}
