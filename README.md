# The LLVM Compiler Infrastructure with Simple RISC-V backend

Follow the tutorial [Writing an LLVM Backend](https://llvm.org/docs/WritingAnLLVMBackend.html)

## build LLVM
```bash
$ cmake -G "Ninja" ../llvm/ -DLLVM_ENABLE_PROJECTS="clang;lld;" -DCMAKE_BUILD_TYPE=Debug -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD="myRISCV"
$ ninja
```

## Execution

```bash
$ llc -march=myriscv -filetype=asm test.ll -o test.s
```

## Input LLVM IR file

test.ll
```
define i32 @test() {
    ret i32 0
}
```

## Output result

test.s

```
	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0
	.file	"test.ll"
	.text
	.globl	test                            # -- Begin function test
	.type	test,@function
test:                                   # @test
	.cfi_startproc
# %bb.0:
	addi	x10, x0, 0
	jalr	x0, x1, 0
.Lfunc_end0:
	.size	test, .Lfunc_end0-test
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
```
