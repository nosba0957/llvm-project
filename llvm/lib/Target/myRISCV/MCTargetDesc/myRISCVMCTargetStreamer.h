#ifndef LLVM_LIB_TARGET_MYRISCV_MCTARGETDESC_MYRISCVTARGETSTREAMER_H
#define LLVM_LIB_TARGET_MYRISCV_MCTARGETDESC_MYRISCVTARGETSTREAMER_H

#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/FormattedStream.h"

namespace llvm {

class formatted_raw_ostream;

class myRISCVTargetStreamer : public MCTargetStreamer {
public:
  myRISCVTargetStreamer(MCStreamer &S);
};

class myRISCVTargetAsmStreamer : public myRISCVTargetStreamer {
  formatted_raw_ostream &OS;

public:
  myRISCVTargetAsmStreamer(MCStreamer &S, formatted_raw_ostream &OS);
};

} // namespace llvm

#endif
