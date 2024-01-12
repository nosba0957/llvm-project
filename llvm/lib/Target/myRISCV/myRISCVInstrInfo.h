#define GET_INSTRINFO_OPERAND_ENUM // For OpName enum
#include "myRISCVGenInstrInfo.inc"

#include "llvm/CodeGen/TargetInstrInfo.h"

namespace llvm {
namespace myRISCV {
  int16_t getNamedOperandIdx(uint16_t Opcode, uint16_t NamedIndex);
}
class myRISCVInstrInfo : public myRISCVGenInstrInfo {

public:
  myRISCVInstrInfo();
};
} // End namespace llvm
