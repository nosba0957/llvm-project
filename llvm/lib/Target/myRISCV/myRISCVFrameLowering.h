#ifndef LLVM_LIB_TARGET_MYRISCV_MYRISCVFRAMELOWERING_H
#define LLVM_LIB_TARGET_MYRISCV_MYRISCVFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm{
class myRISCVSubtarget;

class myRISCVFrameLowering : public TargetFrameLowering {
private:
  const myRISCVSubtarget &STI;
public:
  explicit myRISCVFrameLowering(const myRISCVSubtarget &STI);  

  void emitPrologue(MachineFunction &MF,
                    MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF,
                    MachineBasicBlock &MBB) const override;
  
  bool hasFP(const MachineFunction &MF) const override;

};
}

#endif
