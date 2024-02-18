#include "myRISCVInstrInfo.h"

#define GET_INSTRINFO_CTOR_DTOR
#define GET_INSTRINFO_ENUM
#include "myRISCVGenInstrInfo.inc"

using namespace llvm;

myRISCVInstrInfo::myRISCVInstrInfo()
    : myRISCVGenInstrInfo(myRISCV::ADJCALLSTACKDOWN, myRISCV::ADJCALLSTACKUP) {}
