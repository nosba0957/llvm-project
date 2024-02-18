add_llvm_component_library(LLVMmyRISCVDesc
  myRISCVInstPrinter.cpp
  myRISCVMCCodeEmitter.cpp
  myRISCVMCTargetDesc.cpp
  myRISCVMCObjectFileInfo.cpp
  myRISCVMCTargetStreamer.cpp
  myRISCVMCAsmInfo.cpp

  LINK_COMPONENTS
  MC
  myRISCVInfo
  Support
  TargetParser

  ADD_TO_COMPONENT
  myRISCV
)
