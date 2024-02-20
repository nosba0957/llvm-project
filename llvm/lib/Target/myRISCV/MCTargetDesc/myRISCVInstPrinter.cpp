#include "MCTargetDesc/myRISCVInstPrinter.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCRegister.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>

using namespace llvm;

#define PRINT_ALIAS_INSTR
#include "myRISCVGenAsmWriter.inc"

void myRISCVInstPrinter::printInst(const MCInst *MI, uint64_t Address,
                                   StringRef Annot, const MCSubtargetInfo &STI,
                                   raw_ostream &OS) {
  const MCInst *NewMI = MI;
  if (!PrintAliases || !printAliasInstr(NewMI, Address, STI, OS)) {
    printInstruction(NewMI, Address, STI, OS);
  }
  printAnnotation(OS, Annot);
}

void myRISCVInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                      const MCSubtargetInfo &STI,
                                      raw_ostream &OS, const char *Modifier) {
  const MCOperand &MO = MI->getOperand(OpNo);

  if (MO.isReg()) {
    printRegName(OS, MO.getReg());
    return;
  }

  if (MO.isImm()) {
    markup(OS, Markup::Immediate) << formatImm(MO.getImm());
    return;
  }
  assert(MO.isExpr() && "Unknown operand kind in printOperand");
  MO.getExpr()->print(OS, &MAI);
}

void myRISCVInstPrinter::printRegName(raw_ostream &OS, MCRegister Reg) const {
  markup(OS, Markup::Register) << getRegisterName(Reg);
}
