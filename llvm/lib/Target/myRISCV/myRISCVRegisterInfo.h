#ifndef LLVM_LIB_TARGET_MYRISCV_MYRISCVREGISTERINFO_H
#define LLVM_LIB_TARGET_MYRISCV_MYRISCVREGISTERINFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "myRISCVGenRegisterInfo.inc"

namespace llvm{
class myRISCVRegisterInfo : public myRISCVGenRegisterInfo {
public:
  myRISCVRegisterInfo(unsigned HwMode);
  
  const MCPhysReg* getCalleeSavedRegs(const MachineFunction *MF) const override;
  BitVector getReservedRegs(const MachineFunction &MF) const override;
  bool eliminateFrameIndex(MachineBasicBlock::iterator MI,
                           int SPAdj, unsigned FIOperandNum,
                           RegScavenger *RS) const override;

  Register getFrameRegister(const MachineFunction &MF) const override;
};
}

#endif
