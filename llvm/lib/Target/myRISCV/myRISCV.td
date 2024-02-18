include "llvm/Target/Target.td"

def RV32 : HwMode<"", []>;
def RV64 : HwMode<"+64bit", []>;

include "myRISCVRegisterInfo.td"
include "myRISCVInstrInfo.td"
include "myRISCVCallingConv.td"

def myRISCVInstrInfo : InstrInfo;

def RISCVAsmWriter : AsmWriter {
  int PassSubtarget = 1;
}

def myRISCV : Target {
  let InstructionSet = myRISCVInstrInfo;
  let AssemblyWriters = [RISCVAsmWriter];
}

def : ProcessorModel<"myriscv", NoSchedModel, []>; // in Target.td
