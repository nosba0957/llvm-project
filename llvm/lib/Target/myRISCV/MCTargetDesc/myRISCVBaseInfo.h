#ifndef LLVM_LIB_TARGET_MYRISCV_MCTARGETDESC_MYRISCVBASEINFO_H
#define LLVM_LIB_TARGET_MYRISCV_MCTARGETDESC_MYRISCVBASEINFO_H

#include "myRISCVMCTargetDesc.h"

namespace llvm {

namespace myRISCVII {
enum {
  InstFormatPseudo = 0,
  InstFormatR = 1,
  InstFormatI = 2,
  InstFormatS = 3,
  InstFormatB = 4,
  InstFormatU = 5,
  InstFormatJ = 6
};
} // namespace myRISCVII

namespace myRISCVOp {
enum OperandType : unsigned { OPERAND_SIMM12, OPERAND_UNKNOWN };
} // namespace myRISCVOp
} // namespace llvm

#endif
