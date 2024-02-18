#include "myRISCVMCTargetStreamer.h"

using namespace llvm;

myRISCVTargetStreamer::myRISCVTargetStreamer(MCStreamer &S)
    : MCTargetStreamer(S) {}

myRISCVTargetAsmStreamer::myRISCVTargetAsmStreamer(MCStreamer &S,
                                                   formatted_raw_ostream &OS)
    : myRISCVTargetStreamer(S), OS(OS) {}
