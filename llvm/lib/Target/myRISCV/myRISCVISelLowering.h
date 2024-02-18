#ifndef LLVM_LIB_TARGET_MYRISCV_MYRISCVISELLOWERING_H
#define LLVM_LIB_TARGET_MYRISCV_MYRISCVISELLOWERING_H

#include "llvm/CodeGen/SelectionDAGNodes.h"
#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/IR/LLVMContext.h"

namespace llvm {
class myRISCVTargetMachine;
class myRISCVSubtarget;

namespace myRISCVISD {
enum NodeType : unsigned { FIRST_NUMBER = ISD::BUILTIN_OP_END, RET_GLUE };
}

class myRISCVTargetLowering : public TargetLowering {
  const myRISCVSubtarget &STI;

public:
  myRISCVTargetLowering(const myRISCVTargetMachine &TM,
                        const myRISCVSubtarget &sti);

  SDValue LowerFormalArguments(
      SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
      const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &dl,
      SelectionDAG &DAG,
      SmallVectorImpl<SDValue> &InVals) const override; // must implement

  SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
                      const SmallVectorImpl<ISD::OutputArg> &Outs,
                      const SmallVectorImpl<SDValue> &OutVals, const SDLoc &dl,
                      SelectionDAG &DAG) const override;

  unsigned getNumRegistersForCallingConv(LLVMContext &Context,
                                         CallingConv::ID CC,
                                         EVT VT) const override;

  MVT getRegisterTypeForCallingConv(LLVMContext &Context, CallingConv::ID CC,
                                    EVT VT) const override;
};
} // End namespace llvm

#endif
