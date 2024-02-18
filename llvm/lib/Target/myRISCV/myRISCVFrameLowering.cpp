#include "myRISCVFrameLowering.h"

using namespace llvm;

myRISCVFrameLowering::myRISCVFrameLowering(const myRISCVSubtarget &sti)
    : TargetFrameLowering(StackGrowsDown, Align(16), 0), STI(sti) {}

void myRISCVFrameLowering::emitPrologue(MachineFunction &MF,
                                        MachineBasicBlock &MBB) const {
}

void myRISCVFrameLowering::emitEpilogue(MachineFunction &MF,
                                        MachineBasicBlock &MBB) const {
}

bool myRISCVFrameLowering::hasFP(const MachineFunction &MF) const {
  return false;
}
