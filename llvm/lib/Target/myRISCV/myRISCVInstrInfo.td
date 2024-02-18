include "myRISCVInstrFormats.td"

def myRISCVRetFlag : SDNode<"myRISCVISD::RET_GLUE", SDTNone,
                            [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

def simm12 : Operand<XLenVT>, ImmLeaf<XLenVT, [{return isInt<12>(Imm);}]>{
  bits<12> imm;
  let OperandNamespace = "myRISCVOp";
}
def simm20 : Operand<XLenVT>, ImmLeaf<XLenVT, [{return isInt<32>(Imm) && !(Imm & 0x0fff);}]>{
  bits<20> imm;
  let OperandNamespace = "myRISCVOp";
}

class ALU_r<bits<7> opcode, bits<3> func3, bits<7> func7, string instr>
           : RInstr<opcode, func3, func7, (outs GPR:$rd), (ins GPR:$rs1, GPR:$rs2),
                    !strconcat(instr, "\t$rd, $rs1, $rs2")>{ // TODO: Commutable flag
}

class ALU_i<bits<7> opcode, bits<3> func3, string instr, Operand Op>
           : IInstr<opcode, func3, (outs GPR:$rd), (ins GPR:$rs1, Op:$imm12),
                    !strconcat(instr, "\t$rd, $rs1, $imm12")>{
}

class ALU_u<bits<7> opcode, string instr, Operand Op>
           : UInstr<opcode, (outs GPR:$rd), (ins Op:$imm20),
                    !strconcat(instr, "\t$rd, $imm20")>{
}

def SDT_CallSeqStart : SDCallSeqStart<[SDTCisVT<0, i32>, SDTCisVT<1, i32>]>;
def SDT_CallSeqEnd   : SDCallSeqEnd  <[SDTCisVT<0, i32>, SDTCisVT<1, i32>]>;
def CallSeqStart : SDNode<"ISD::CALLSEQ_START", SDT_CallSeqStart, [SDNPHasChain, SDNPOutGlue]>;
def CallSeqEnd   : SDNode<"ISD::CALLSEQ_END"  , SDT_CallSeqEnd  , [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue]>;

let Defs = [X2], Uses = [X2], hasSideEffects = 1 in {
  def ADJCALLSTACKDOWN : Pseudo<(outs), (ins simm12:$amt1, simm12:$amt2), "", [(CallSeqStart timm:$amt1, timm:$amt2)]>;
  def ADJCALLSTACKUP   : Pseudo<(outs), (ins simm12:$amt1, simm12:$amt2), "", [(CallSeqEnd   timm:$amt1, timm:$amt2)]>;
}

def ADDI : ALU_i<0b0010011, 0b000, "addi", simm12>;
def ADD : ALU_r<0b0110011, 0b000, 0b0000000, "add">;
def LUI : ALU_u<0b0110111, "lui", simm20>;

def JALR : ALU_i<0b1100111, 0b000, "jalr", simm12>;

def myriscv_ret_glue  : SDNode<"myRISCVISD::RET_GLUE", SDTNone,
                             [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;
def PseudoRET : Pseudo<(outs), (ins), "ret", [(myriscv_ret_glue)]>,
                PseudoInstExpansion<(JALR X0, X1, 0)> {
  let isPseudo = 1;
  let isReturn = 1;
  let isTerminator = 1;
}
