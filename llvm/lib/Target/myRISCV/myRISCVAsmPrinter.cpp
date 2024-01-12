#include "myRISCVTargetMachine"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/MC/MCStreamer.h"
 
using namespace llvm;

class myRISCVAsmPrinter : public AsmPrinter {
public:
  myRISCVAsmPrinter(TargetMachine &TM,
                    std::unique_ptr<MCStreamer> Streamer)
    : AsmPrinter(TM, std::move(Streamer)) {}
  
  StringRef getPassName() const override { return "myRISCV Assembly Printer"; }
  
};
