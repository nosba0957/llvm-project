include "myRISCVInstrFormats.td"

def imm12 : Operand<XLenVT>{
  bits<12> imm;
  let OperandNamespace = "myRISCVOp";
}
def imm20 : Operand<XLenVT>{
  bits<20> imm;
  let OperandNamespace = "myRISCVOp";
}

class ALU_r<bits<7> opcode, bits<3> func3, bits<7> func7, string instr>
           : RInstr<opcode, func3, func7, (outs GPR:$rd), (ins GPR:$rs1, GPR:$rs2), instr>{ // TODO: Commutable flag
}

class ALU_i<bits<7> opcode, bits<3> func3, string instr>
           : IInstr<opcode, func3, (outs GPR:$rd), (ins GPR:$rs1, imm12:$imm), instr>{
}

class ALU_u<bits<7> opcode, string instr>
           : UInstr<opcode, (outs GPR:$rd), (ins imm20:$imm), instr>{
}

def ADDI : ALU_r<0b0010011, 0b000, "addi">;
def ADD : ALU_i<0b0110011, 0b000, 0b0000000, "add">;
def LUI : ALU_u<0b0110111, "lui">;
