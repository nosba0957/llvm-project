add_llvm_component_library(LLVMmyRISCVInfo
  myRISCVTargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  myRISCV
)
