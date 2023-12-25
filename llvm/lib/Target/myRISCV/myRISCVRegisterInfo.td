let Namespace = "myRISCV" in {

class myRISCVReg<bits<5> enc, list<string> alt = []> : Register<n> {
  let HWEcoding{4:0} = enc;
  let AltNames = alt;
}
def X0 : myRISCVReg<0, ["zero"]>, DwarfRegNum<[0]>;
def X1 : myRISCVReg<1, ["ra"]>, DwarfRegNum<[1]>;
def X2 : myRISCVReg<2, ["sp"]>, DwarfRegNum<[2]>;
def X3 : myRISCVReg<3, ["gp"]>, DwarfRegNum<[3]>;
def X4 : myRISCVReg<4, ["tp"]>, DwarfRegNum<[4]>;
def X5 : myRISCVReg<5, ["t0"]>, DwarfRegNum<[5]>;
def X6 : myRISCVReg<6, ["t1"]>, DwarfRegNum<[6]>;
def X7 : myRISCVReg<7, ["t2"]>, DwarfRegNum<[7]>;
def X8 : myRISCVReg<8, ["s0", "fp"]>, DwarfRegNum<[8]>;
def X9 : myRISCVReg<9, ["s1"]>, DwarfRegNum<[9]>;
def X10 : myRISCVReg<10, ["a0"]>, DwarfRegNum<[10]>;
def X11 : myRISCVReg<11, ["a1"]>, DwarfRegNum<[11]>;
def X12 : myRISCVReg<12, ["a2"]>, DwarfRegNum<[12]>;
def X13 : myRISCVReg<13, ["a3"]>, DwarfRegNum<[13]>;
def X14 : myRISCVReg<14, ["a4"]>, DwarfRegNum<[14]>;
def X15 : myRISCVReg<15, ["a5"]>, DwarfRegNum<[15]>;
def X16 : myRISCVReg<16, ["a6"]>, DwarfRegNum<[16]>;
def X17 : myRISCVReg<17, ["a7"]>, DwarfRegNum<[17]>;
def X18 : myRISCVReg<18, ["s2"]>, DwarfRegNum<[18]>;
def X19 : myRISCVReg<19, ["s3"]>, DwarfRegNum<[19]>;
def X20 : myRISCVReg<20, ["s4"]>, DwarfRegNum<[20]>;
def X21 : myRISCVReg<21, ["s5"]>, DwarfRegNum<[21]>;
def X22 : myRISCVReg<22, ["s6"]>, DwarfRegNum<[22]>;
def X23 : myRISCVReg<23, ["s7"]>, DwarfRegNum<[23]>;
def X24 : myRISCVReg<24, ["s8"]>, DwarfRegNum<[24]>;
def X25 : myRISCVReg<25, ["s9"]>, DwarfRegNum<[25]>;
def X26 : myRISCVReg<26, ["s10"]>, DwarfRegNum<[26]>;
def X27 : myRISCVReg<27, ["s11"]>, DwarfRegNum<[27]>;
def X28 : myRISCVReg<28, ["t3"]>, DwarfRegNum<[28]>;
def X29 : myRISCVReg<29, ["t4"]>, DwarfRegNum<[29]>;
def X30 : myRISCVReg<30, ["t5"]>, DwarfRegNum<[30]>;
def X31 : myRISCVReg<31, ["t6"]>, DwarfRegNum<[31]>;
}

def XLenVT : ValueTypeByHwMode<[RV32, RV64],
                               [i32, i64]>;

def GPR : RegisterClass<"myRISCV", XLenVT, 32,
  (add X0, X1, X2, X3, X4,
  X5, X6, X7, X8, X9, X10,
  X11, X12, X13, X14, X15,
  X16, X17, X18, X19, X20,
  X21, X22, X23, X24, X25,
  26, X27, X28, X29, X30,
  X31)>{
    let RegInfos = XLenVT;
}

