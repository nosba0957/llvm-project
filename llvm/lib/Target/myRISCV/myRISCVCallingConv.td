def CSR_ILP32_LP64
    : CalleeSavedRegs<(add X2, X8, X9, X18, X19,
                        X20, X21, X22, X23, X24,
                        X25, X26, X27)>;
