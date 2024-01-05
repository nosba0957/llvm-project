// RISC-V instruction general formats

class myRISCVInstr<dag outs, dag ins, string asmstr, list<dag> pattern,
            InstrItinClass itin = NoItinerary>
  : Instruction {
  bits<32> Instr;

  let Namespace = "myRISCV";
  let OutOperandList = outs;
  let InOperandList = ins;
  let Pattern = pattern;
  
  let Itinerary = itin;
}

// RISC-V R-type instruction

class RInstr<bits<7> opcode, bits<3> func3, bits<7> func7,
             dag outs, dag ins, string asmstr, list<dag> pattern,
             InstrItinClass itin = NoItinerary>
  : myRISCVInstr<outs, ins, asmstr, patttern, itin> {
  bits<5> rd;
  bits<5> rs1;
  bits<5> rs2;
  
  let Instr{6:0} = opcode;
  let Instr{11:7} = rd;
  let Instr{14:12} = func3;
  let Instr{19:15} = rs1;
  let Instr{24:20} = rs2;
  let Instr{31:25} = func7;
}

// RISC-V I-type instruction

class IInstr<bits<7> opcode, bits<3> func3, dag outs, dag ins,
             string asmstr, list<dag> pattern,
             InstrItinClass itin = NoItinerary>
  : myRISCVInstr<outs, ins, asmstr, pattern, itin> {
  bits<5> rd;
  bits<5> rs1;
  bits<12> imm12;
  
  let Instr{6:0} = opcode;
  let Instr{11:7} = rd;
  let Instr{14:12} = func3;
  let Instr{19:15} = rs1;
  let Instr{31:20} = imm12;

}

// RISC-V S-type instruction

class SInstr<bits<7> opcode, bits<3> func3, dag outs, dag ins,
             string asmstr, list<dag> pattern,
             InstrItinClass itin = NoItinerary>
  : myRISCVInstr<outs, ins, asmstr, pattern, itin> {
  bits<5> rs1;
  bits<5> rs2;
  bits<12> imm12;

  let Instr{6:0} = opcode;
  let Instr{11:7} = imm12{4:0};
  let Instr{14:12} = func3;
  let Instr{19:15} = rs1;
  let Instr{24:20} = rs2;
  let Instr{31:25} = imm12{11:5};

}

// RISC-V B-type instruction

class BInstr<bits<7> opcode, bits<3> func3, dag outs, dag ins,
             string asmstr, list<dag> pattern,
             InstrItinClass itin = NoItinerary>
  : myRISCVInstr<outs, ins, asmstr, pattern, itin> {
  bits<5> rs1;
  bits<5> rs2;
  bits<12> imm12;

  let Instr{6:0} = opcode;
  let Instr{7} = imm12{11};
  let Instr{11:8} = imm12{4:1};
  let Instr{14:12} = func3;
  let Instr{19:15} = rs1;
  let Instr{24:20} = rs2;
  let Instr{30:25} = imm12{10:5};
  let Instr{31} = imm12{12};

}

// RISC-V U-type instruction

class UInstr<bits<7> opcode, dag outs, dag ins,
             string asmstr, list<dag> pattern,
             InstrItinClass itin = NoItinerary>
  : myRISCVInstr<outs, ins, asmstr, pattern, itin> {
   bits<5> rd;
   bits<20> imm20;
   
   let Instr{6:0} = opcode;
   let Instr{11:7} = rd;
   let Instr{31:12} = imm20;
 
}

// RISC-V J-type instruction

class JInstr<bits<7>opcode, dag outs, dag ins,
             string asmstr, list<dag> pattern,
             InstrItinClass itin = NoItinerary>
  : myRISCVInstr<outs, ins, asmstr, pattern, itin> {
  bits<5> rd;
  bits<20> imm20;
  
  let Instr{6:0} = opcode;
  let Instr{11:7} = rd;
  let Instr{19:12} = imm20{19:12};
  let Instr{20} = imm20{11};
  let Instr{30:21} = imm20{10:1};
  let Instr{31} = imm20{20};
}
