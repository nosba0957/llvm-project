#include "myRISCVISelLowering.h"
#include "myRISCVRegisterInfo.h"
#include "myRISCVTargetMachine.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/SelectionDAGNodes.h"

using namespace llvm;

#define GET_REGINFO_ENUM
#include "myRISCVGenRegisterInfo.inc"

#include "myRISCVGenCallingConv.inc"

myRISCVTargetLowering::myRISCVTargetLowering(const myRISCVTargetMachine &TM,
                                             const myRISCVSubtarget &sti)
    : TargetLowering(TM), STI(sti) {
  addRegisterClass(MVT::i64, &myRISCV::GPRRegClass); // for type legalization
}
SDValue myRISCVTargetLowering::LowerFormalArguments(
    SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &dl,
    SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const {
  SmallVector<CCValAssign, 16> ArgLocs;
  MachineFunction &MF = DAG.getMachineFunction();
  CCState CCInfo(CallConv, isVarArg, MF, ArgLocs, *DAG.getContext());
  CCInfo.AnalyzeFormalArguments(Ins, CC_myRISCV);

  for (unsigned i = 0, e = ArgLocs.size(); i < e; ++i) {
    CCValAssign &VA = ArgLocs[i];
  }
  return Chain;
}

SDValue
myRISCVTargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                                   bool isVarArg,
                                   const SmallVectorImpl<ISD::OutputArg> &Outs,
                                   const SmallVectorImpl<SDValue> &OutVals,
                                   const SDLoc &DL, SelectionDAG &DAG) const {
  SmallVector<CCValAssign, 16> RVLocs;

  CCState CCInfo(CallConv, isVarArg, DAG.getMachineFunction(), RVLocs,
                 *DAG.getContext());
  CCInfo.AnalyzeReturn(Outs, RetCC_myRISCV);

  SDValue Glue;
  SmallVector<SDValue, 4> RetOps(1, Chain);

  for (unsigned i = 0, e = RVLocs.size(); i < e; ++i) {
    CCValAssign &VA = RVLocs[i];
    assert(VA.isRegLoc() && "Can only return in registers!");
    Chain = DAG.getCopyToReg(Chain, DL, VA.getLocReg(), OutVals[i], Glue);
    Glue = Chain.getValue(1);
    RetOps.push_back(DAG.getRegister(VA.getLocReg(), VA.getLocVT()));
  }
  RetOps[0] = Chain;

  if (Glue.getNode()) {
    RetOps.push_back(Glue);
  }
  return DAG.getNode(myRISCVISD::RET_GLUE, DL, MVT::Other, RetOps);
}

unsigned
myRISCVTargetLowering::getNumRegistersForCallingConv( // for type legalization
    LLVMContext &Context, CallingConv::ID CC, EVT VT) const {
  return 1;
}

// for type legalization
MVT myRISCVTargetLowering::getRegisterTypeForCallingConv(LLVMContext &Context,
                                                         CallingConv::ID CC,
                                                         EVT VT) const {
  return MVT::i64;
}
