#ifndef LLVM_LIB_TARGET_MYRISCV_MYRISCVSUBTARGET_H
#define LLVM_LIB_TARGET_MYRISCV_MYRISCVSUBTARGET_H

#include "myRISCV.h"
#include "myRISCVFrameLowering.h"
#include "myRISCVISelLowering.h"
#include "myRISCVInstrInfo.h"
#include "myRISCVRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "myRISCVGenSubtargetInfo.inc"

#define DEBUG_TYPE "myriscv-subtarget"

namespace llvm {
class StringRef;
class myRISCVTargetMachine;

class myRISCVSubtarget : public myRISCVGenSubtargetInfo {
protected:
  MVT XLenVT = MVT::i32;
  Triple TargetTriple;
  const myRISCVTargetMachine &TM;
  myRISCVFrameLowering FrameLowering;
  myRISCVInstrInfo InstrInfo;
  myRISCVRegisterInfo RegInfo;
  myRISCVTargetLowering TLInfo;
  SelectionDAGTargetInfo TSInfo;

public:
  myRISCVSubtarget(const Triple &TT, StringRef CPU, StringRef TuneCPU,
                   StringRef FS, const myRISCVTargetMachine &TTM);
  ~myRISCVSubtarget() override;

  myRISCVSubtarget &initializeSubtargetDependencies(const Triple &TT,
                                                    StringRef CPU,
                                                    StringRef TuneCPU,
                                                    StringRef FS);

  const myRISCVInstrInfo *getInstrInfo() const override { return &InstrInfo; }
  const myRISCVFrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }
  const myRISCVRegisterInfo *getRegisterInfo() const override {
    return &RegInfo;
  }
  const myRISCVTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }
  const SelectionDAGTargetInfo *getSelectionDAGInfo() const override {
    return &TSInfo;
  }

  bool enableMachineScheduler() const override {
    return true;
  } // this function decide using which dag scheduler

  // autogen by tablegen
  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);
};
} // namespace llvm

#endif
