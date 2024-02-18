def CSR_ILP32_LP64
    : CalleeSavedRegs<(add X2, X8, X9, X18, X19,
                        X20, X21, X22, X23, X24,
                        X25, X26, X27)>;
def RetCC_myRISCV : CallingConv<[
                      CCIfType<[i1, i8, i16, i32, i64], CCAssignToReg<[X10, X11]>>,
                      CCIfType<[i32], CCAssignToStack<4, 4>>,
                    ]>;
def CC_myRISCV : CallingConv<[
                    CCIfType<[i1, i8, i16, i32, i64], CCAssignToReg<[X10, X11, X12, X13, X14, X15, X16, X17]>>,
                    CCIfType<[i32], CCAssignToStack<4, 4>>,
                 ]>;
