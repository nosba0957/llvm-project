include "llvm/Target/Target.td"

include "myRISCVRegisterInfo.td"
include "myRISCVInstrInfo.td"
include "myRISCVCallingConv.td"

def myRISCInstrInfo : InstrInfo {
}

def myRISCV : Target {
}
