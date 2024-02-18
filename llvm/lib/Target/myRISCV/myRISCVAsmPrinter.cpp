#include "TargetInfo/myRISCVTargetInfo.h"
#include "myRISCVTargetMachine.h"
#include "llvm-c/Target.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/TargetRegistry.h"

#include <iostream>

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

class myRISCVAsmPrinter : public AsmPrinter {
public:
  myRISCVAsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)) {}

  StringRef getPassName() const override { return "myRISCV Assembly Printer"; }

  void emitInstruction(const MachineInstr *MI) override;

private:
  bool emitPseudoExpansionLowering(MCStreamer &OutStreamer,
                                   const MachineInstr *MI);

  bool lowerToMCInst(const MachineInstr *MI, MCInst &OutMI);
};

#define GET_INSTRINFO_ENUM
#include "myRISCVGenInstrInfo.inc"
#define GET_REGINFO_ENUM
#include "myRISCVGenRegisterInfo.inc"

#include "myRISCVGenMCPseudoLowering.inc"

void myRISCVAsmPrinter::emitInstruction(const MachineInstr *MI) {
  std::cout << "emitInstruction\n";
  if (emitPseudoExpansionLowering(*OutStreamer, MI)) {
    return;
  }
  MCInst OutInst;
  if (!lowerToMCInst(MI, OutInst))
    EmitToStreamer(*OutStreamer, OutInst);
}

bool myRISCVAsmPrinter::lowerToMCInst(const MachineInstr *MI, MCInst &OutInst) {
  return false;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializemyRISCVAsmPrinter() {
  RegisterAsmPrinter<myRISCVAsmPrinter> X(getmyRISCVTarget());
}
