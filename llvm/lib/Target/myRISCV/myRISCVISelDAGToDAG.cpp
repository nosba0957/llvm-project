#include "myRISCVISelDAGToDAG.h"

using namespace llvm;

void myRISCVSelectionDAGISel::Select(SDNode *Node) {
  if (Node->isMachineOpcode()) {
    Node->setNodeId(-1);
    return;
  }
  SelectCode(Node);
}
