#include "myRISCVTargetObjectFile.h"

using namespace llvm;

void myRISCVTargetObjectFile::Initialize(MCContext &Ctx,
                                         const TargetMachine &TM) {
  TargetLoweringObjectFile::Initialize(Ctx, TM);
  InitializeELF(TM.Options.UseInitArray);
  this->TM = &static_cast<const myRISCVTargetMachine &>(TM);
}
