#ifndef LLVM_LIB_TARGET_MYRISCV_MCTARGETDESC_MYRISCVMCTARGETDESC_H
#define LLVM_LIB_TARGET_MYRISCV_MCTARGETDESC_MYRISCVMCTARGETDESC_H

#include "llvm/MC/MCTargetOptions.h"
#include "llvm/Support/DataTypes.h"
#include <memory>

namespace llvm {
class Target;
class MCContext;
class MCCodeEmitter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCInstrInfo;

MCCodeEmitter *createmyRISCVMCCodeEmitter(const MCInstrInfo &MCII,
                                          MCContext &Ctx);
} // namespace llvm

#define GET_REGINFO_ENUM
#include "myRISCVGenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#define GET_INSTRINFO_MC_HELPER_DECLS
#include "myRISCVGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "myRISCVGenSubtargetInfo.inc"

#endif
