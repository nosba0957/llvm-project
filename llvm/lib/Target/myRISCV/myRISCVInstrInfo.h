#ifndef LLVM_LIB_TARGET_MYRISCV_MYRISCVINSTRINFO_H
#define LLVM_LIB_TARGET_MYRISCV_MYRISCVINSTRINFO_H

#include "myRISCV.h"
#include "myRISCVRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "myRISCVGenInstrInfo.inc"

namespace llvm {
class myRISCVInstrInfo : public myRISCVGenInstrInfo {

public:
  myRISCVInstrInfo();
};
} // End namespace llvm

#endif
