#ifndef LLVM_LIB_TARGET_MYRISCV_MYRISCVISELDAGTODAG_H
#define LLVM_LIB_TARGET_MYRISCV_MYRISCVISELDAGTODAG_H

#include "myRISCV.h"
#include "myRISCVTargetMachine.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

namespace llvm {
  class myRISCVSelectionDAGISel : public SelectionDAGISel {
  public:
    myRISCVSelectionDAGISel(char ID, TargetMachine &tm, CodeGenOptLevel OL)
    : SelectionDAGISel(ID, tm, OL) {}
    
    void Select(SDNode *N) override;
  };
}

#endif
