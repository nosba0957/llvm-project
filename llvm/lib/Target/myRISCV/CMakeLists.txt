add_llvm_component_group(myRISCV)

set(LLVM_TARGET_DEFINITIONS myRISCV.td)

tablegen(LLVM myRISCVGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM myRISCVGenInstrInfo.inc -gen-register-info)

add_public_tablegen_target(myRISCVCommonTableGen)

add_llvm_target(
  myRISCVRegisterInfo.cpp
  myRISCVTargetmachine.cpp
  myRISCVInstrInfo.cpp
  myRISCVISelDAGToDAG.cpp
  myRISCVISelLowering.cpp
  myRISCVAsmPrinter.cpp
)

add_subdirectory(TargetInfo)

