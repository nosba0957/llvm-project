#ifndef LLVM_LIB_TARGET_MYRISCV_MCTARGETDESC_MYRISCVMCASMINFO_H
#define LLVM_LIB_TARGET_MYRISCV_MCTARGETDESC_MYRISCVMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class Triple;

class myRISCVMCAsmInfo : public MCAsmInfoELF {

public:
  myRISCVMCAsmInfo(const Triple &TargetTriple);
};
} // end namespace llvm

#endif
