add_llvm_component_group(myRISCV)

set(LLVM_TARGET_DEFINITIONS myRISCV.td)

tablegen(LLVM myRISCVGenRegisterInfo.inc -gen-register-info)

add_public_tablegen_target()

add_llvm_target(
  myRISCVRegisterInfo.cpp
  myRISCVTargetmachine.cpp
  LINK_COMPONENTS
  Analysis
  AsmPrinter
  BinaryFormat
  CodeGen
  CodeGenTypes
  Core
  GlobalISel
  MC
  PowerPCDesc
  PowerPCInfo
  Scalar
  SelectionDAG
  Support
  Target
  TargetParser
  TransformUtils

  ADD_TO_COMPONENT
  PowerPC
  )

add_subdirectory(TargetInfo)
