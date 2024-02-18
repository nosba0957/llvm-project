// RISC-V instruction general formats

class Format<bits<5> val> {
  bits<5> Value = val;
}
def FormatPseudo : Format<0>;
def FormatR      : Format<1>;
def FormatI      : Format<2>;
def FormatS      : Format<3>;
def FormatB      : Format<4>;
def FormatU      : Format<5>;
def FormatJ      : Format<6>;

class myRISCVInstr<dag outs, dag ins, string asmstr,
                   list<dag> pattern, Format format>
  : Instruction {
  field bits<32> Instr;
  bits<7> Opcode = 0;

  let Instr{6-0} = Opcode;
  let Namespace = "myRISCV";
  let OutOperandList = outs;
  let InOperandList = ins;
  let Pattern = pattern;
  let AsmString = asmstr;

}

// RISC-V R-type instruction

class RInstr<bits<7> opcode, bits<3> func3, bits<7> func7,
             dag outs, dag ins, string asmstr>
  : myRISCVInstr<outs, ins, asmstr, [], FormatR> {
  bits<5> rd;
  bits<5> rs1;
  bits<5> rs2;

  let Instr{6-0} = opcode;
  let Instr{11-7} = rd;
  let Instr{14-12} = func3;
  let Instr{19-15} = rs1;
  let Instr{24-20} = rs2;
  let Instr{31-25} = func7;
}

// RISC-V I-type instruction

class IInstr<bits<7> opcode, bits<3> func3, dag outs, dag ins,
             string asmstr>
  : myRISCVInstr<outs, ins, asmstr, [], FormatI> {
  bits<5> rd;
  bits<5> rs1;
  bits<12> imm12;

  let Instr{6-0} = opcode;
  let Instr{11-7} = rd;
  let Instr{14-12} = func3;
  let Instr{19-15} = rs1;
  let Instr{31-20} = imm12;

}

// RISC-V S-type instruction

class SInstr<bits<7> opcode, bits<3> func3, dag outs, dag ins,
             string asmstr>
  : myRISCVInstr<outs, ins, asmstr, [], FormatS> {
  bits<5> rs1;
  bits<5> rs2;
  bits<12> imm12;

  let Instr{6-0} = opcode;
  let Instr{11-7} = imm12{4-0};
  let Instr{14-12} = func3;
  let Instr{19-15} = rs1;
  let Instr{24-20} = rs2;
  let Instr{31-25} = imm12{11-5};

}

// RISC-V B-type instruction

class BInstr<bits<7> opcode, bits<3> func3, dag outs, dag ins,
             string asmstr>
  : myRISCVInstr<outs, ins, asmstr, [], FormatB> {
  bits<5> rs1;
  bits<5> rs2;
  bits<12> imm12;

  let Instr{6-0} = opcode;
  let Instr{7} = imm12{10};
  let Instr{11-8} = imm12{3-0};
  let Instr{14-12} = func3;
  let Instr{19-15} = rs1;
  let Instr{24-20} = rs2;
  let Instr{30-25} = imm12{9-4};
  let Instr{31} = imm12{11};

}

// RISC-V U-type instruction

class UInstr<bits<7> opcode, dag outs, dag ins,
             string asmstr>
  : myRISCVInstr<outs, ins, asmstr, [], FormatU> {
   bits<5> rd;
   bits<20> imm20;

   let Instr{6-0} = opcode;
   let Instr{11-7} = rd;
   let Instr{31-12} = imm20;

}

// RISC-V J-type instruction

class JInstr<bits<7>opcode, dag outs, dag ins,
             string asmstr>
  : myRISCVInstr<outs, ins, asmstr, [], FormatJ> {
  bits<5> rd;
  bits<20> imm20;

  let Instr{6-0} = opcode;
  let Instr{11-7} = rd;
  let Instr{19-12} = imm20{18-11};
  let Instr{20} = imm20{10};
  let Instr{30-21} = imm20{9-0};
  let Instr{31} = imm20{19};
}

class Pseudo<dag outs, dag ins, string asmstr = "", list<dag> pattern>
    : myRISCVInstr<outs, ins, asmstr, pattern, FormatPseudo> {
  let isPseudo = 1;
  let isCodeGenOnly = 1;
}
