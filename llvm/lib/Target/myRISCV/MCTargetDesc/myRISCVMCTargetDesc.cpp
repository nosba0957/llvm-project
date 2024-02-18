#include "myRISCVMCTargetDesc.h"
#include "TargetInfo/myRISCVTargetInfo.h"
#include "myRISCVBaseInfo.h"
#include "myRISCVInstPrinter.h"
#include "myRISCVMCAsmInfo.h"
#include "myRISCVMCTargetStreamer.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

#include "llvm/MC/MCSchedule.h"

#define GET_INSTRINFO_MC_DESC
#define ENABLE_INSTR_PREDICATE_VERIFIER
#include "myRISCVGenInstrInfo.inc"

#define GET_REGINFO_MC_DESC
#include "myRISCVGenRegisterInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "myRISCVGenSubtargetInfo.inc"

using namespace llvm;

static MCAsmInfo *createmyRISCVMCAsmInfo(const MCRegisterInfo &MRI,
                                         const Triple &TT,
                                         const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new myRISCVMCAsmInfo(TT);

  MCRegister SP = MRI.getDwarfRegNum(myRISCV::X2, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, myRISCV::X2, 0);
  MAI->addInitialFrameState(Inst);

  return MAI;
}

static MCInstrInfo *createmyRISCVMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitmyRISCVMCInstrInfo(X); // generated in myRISCVGenInstrInfo.inc
  return X;
}

static MCRegisterInfo *createmyRISCVRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitmyRISCVMCRegisterInfo(X, myRISCV::X1);
  return X;
}

static MCInstPrinter *createmyRISCVMCInstPrinter(const Triple &T,
                                                 unsigned SyntaxVariant,
                                                 const MCAsmInfo &MAI,
                                                 const MCInstrInfo &MII,
                                                 const MCRegisterInfo &MRI) {
  return new myRISCVInstPrinter(MAI, MII, MRI);
}

static MCSubtargetInfo *
createmyRISCVMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  if (CPU.empty() || CPU == "generic")
    CPU = "myriscv";
  return createmyRISCVMCSubtargetInfoImpl(
      TT, CPU, CPU, FS); // function is in myRISCVGenSubtargetInfo.inc
}

static MCInstrAnalysis *createmyRISCVInstrAnalysis(const MCInstrInfo *Info) {
  return new MCInstrAnalysis(Info);
}

static MCTargetStreamer *
createmyRISCVAsmTargetStreamer(MCStreamer &S, formatted_raw_ostream &OS,
                               MCInstPrinter *InstPrint, bool isVerboseAsm) {
  return new myRISCVTargetAsmStreamer(S, OS);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializemyRISCVTargetMC() {
  // I only have one target now
  Target &T = getmyRISCVTarget();

  TargetRegistry::RegisterMCAsmInfo(T, createmyRISCVMCAsmInfo);
  TargetRegistry::RegisterMCInstrInfo(T, createmyRISCVMCInstrInfo);
  TargetRegistry::RegisterMCRegInfo(T, createmyRISCVRegisterInfo);
  TargetRegistry::RegisterMCCodeEmitter(
      T, createmyRISCVMCCodeEmitter); // function is in myRISCVMCCodeEmitter.cpp
  TargetRegistry::RegisterMCInstPrinter(T, createmyRISCVMCInstPrinter);
  TargetRegistry::RegisterMCSubtargetInfo(T, createmyRISCVMCSubtargetInfo);
  TargetRegistry::RegisterMCInstrAnalysis(T, createmyRISCVInstrAnalysis);
  TargetRegistry::RegisterAsmTargetStreamer(T, createmyRISCVAsmTargetStreamer);
}
