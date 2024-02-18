#ifndef LLVM_LIB_TARGET_MYRISCV_MYRISCVISELDAGTODAG_H
#define LLVM_LIB_TARGET_MYRISCV_MYRISCVISELDAGTODAG_H

#include "myRISCV.h"
#include "myRISCVTargetMachine.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

#define GET_INSTRINFO_ENUM
#include "myRISCVGenInstrInfo.inc"

namespace llvm {
class myRISCVDAGToDAGISel : public SelectionDAGISel {

public:
  static char ID;

  myRISCVDAGToDAGISel(TargetMachine &tm, CodeGenOptLevel OL)
      : SelectionDAGISel(ID, tm, OL) {}

  StringRef getPassName() const override {
    return "myRISCV DAG to DAG pattern instruction selection";
  }

  void Select(SDNode *N) override;

private:
#include "myRISCVGenDAGISel.inc"
};
} // namespace llvm

#endif
