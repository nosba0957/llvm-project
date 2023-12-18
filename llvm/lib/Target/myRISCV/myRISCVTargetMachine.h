#ifndef LLVM_LIB_TARGET_myRISCV_myRISCVTARGETMACHINE_H
#define LLVM_LIB_TARGET_myRISCV_myRISCVTARGETMACHINE_H

#include "myRISCVInstrInfo.h"
#include "myRISCVSubtarget.h"
#include "llvm/Target/TargetMachine.h"
#include <optional>

namespace llvm{
class myRISCVTargetMachine : public LLVMTargetMachine {

public:
  // constructor follow the class LLVMTargetMachine
  myRISCVTargetMachine(const Target &T, StringRef DataLayoutString,
                       const Triple &TT, StringRef CPU, StringRef FS,
                       const TargetOptions &Options, Reloc::Model RM,
                       CodeModel::Model CM, CodeGenOptLevel OL);
  
};
}// end namespace llvm
