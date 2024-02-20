#include "TargetInfo/myRISCVTargetInfo.h"
#include "myRISCVTargetMachine.h"
#include "llvm-c/Target.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineOperand.h"
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
  bool lowerOperand(const MachineOperand &MO, MCOperand &MCOp) const;

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
  if (emitPseudoExpansionLowering(*OutStreamer, MI)) {
    return;
  }
  MCInst OutInst;
  if (!lowerToMCInst(MI, OutInst))
    EmitToStreamer(*OutStreamer, OutInst);
}

bool myRISCVAsmPrinter::lowerOperand(const MachineOperand &MO,
                                     MCOperand &MCOp) const {
  switch (MO.getType()) {
  default:
    report_fatal_error("lowerOperand: unknown operand type");
  case MachineOperand::MO_Register:
    if (MO.isImplicit())
      return false;
    MCOp = MCOperand::createReg(MO.getReg());
    break;
  case MachineOperand::MO_Immediate:
    MCOp = MCOperand::createImm(MO.getImm());
    break;
  }
  return true;
}

bool myRISCVAsmPrinter::lowerToMCInst(const MachineInstr *MI, MCInst &OutInst) {
  OutInst.setOpcode(MI->getOpcode());

  for (const MachineOperand &MO : MI->operands()) {
    MCOperand MCOp;
    if (lowerOperand(MO, MCOp))
      OutInst.addOperand(MCOp);
  }
  return false;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializemyRISCVAsmPrinter() {
  RegisterAsmPrinter<myRISCVAsmPrinter> X(getmyRISCVTarget());
}
