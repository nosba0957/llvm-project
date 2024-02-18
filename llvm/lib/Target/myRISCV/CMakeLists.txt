add_llvm_component_group(myRISCV)

set(LLVM_TARGET_DEFINITIONS myRISCV.td)

tablegen(LLVM myRISCVGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM myRISCVGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM myRISCVGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM myRISCVGenCallingConv.inc -gen-callingconv)
tablegen(LLVM myRISCVGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM myRISCVGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM myRISCVGenMCPseudoLowering.inc -gen-pseudo-lowering)

add_public_tablegen_target(myRISCVCommonTableGen)

add_llvm_target(myRISCVCodeGen
  myRISCVRegisterInfo.cpp
  myRISCVTargetMachine.cpp
  myRISCVInstrInfo.cpp
  myRISCVISelDAGToDAG.cpp
  myRISCVISelLowering.cpp
  myRISCVAsmPrinter.cpp
  myRISCVFrameLowering.cpp
  myRISCVSubtarget.cpp
  myRISCVTargetObjectFile.cpp

  LINK_COMPONENTS
  AsmPrinter
  CodeGen
  Core
  MC
  myRISCVDesc
  myRISCVInfo
  SelectionDAG
  Support
  Target

  ADD_TO_COMPONENT
  myRISCV
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
