#include "myRISCVISelDAGToDAG.h"
#include "myRISCV.h"
#include "myRISCVRegisterInfo.h"
#include "llvm/CodeGen/ISDOpcodes.h"
#include "llvm/CodeGen/SelectionDAGNodes.h"
#include "llvm/Pass.h"

#define GET_REGINFO_ENUM
#include "myRISCVGenRegisterInfo.inc"

using namespace llvm;

void myRISCVDAGToDAGISel::Select(SDNode *Node) {
  SDLoc DL(Node);

  switch (Node->getOpcode()) {
  case ISD::Constant: {
    int64_t Imm = cast<ConstantSDNode>(Node)->getSExtValue();
    if (-2048 <= Imm && Imm <= 2048) {
      SDValue SDImm = CurDAG->getTargetConstant(Imm, DL, MVT::i64);
      SDValue SrcReg = CurDAG->getRegister(myRISCV::X0, MVT::i64);
      SDNode *Result =
          CurDAG->getMachineNode(myRISCV::ADDI, DL, MVT::i64, SrcReg, SDImm);
      ReplaceNode(Node, Result);
      return;
    }
  }
  }
  SelectCode(Node);
}

FunctionPass *llvm::createmyRISCVISelDAG(myRISCVTargetMachine &TM,
                                         CodeGenOptLevel OptLevel) {
  return new myRISCVDAGToDAGISel(TM, OptLevel);
}

char myRISCVDAGToDAGISel::ID = 0;
