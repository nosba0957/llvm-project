; RUN: opt < %s -aa-pipeline=tbaa,basic-aa -passes=aa-eval -evaluate-aa-metadata \
; RUN:     -print-no-aliases -print-may-aliases -disable-output 2>&1 | \
; RUN:     FileCheck %s
; RUN: opt < %s -aa-pipeline=tbaa,basic-aa -passes=gvn -S | FileCheck %s --check-prefix=OPT
;
; Check that TBAA handles access tags with aggregate final access types
; correctly.

%A = type { i32, i32 }  ; struct A { int i, j; };
%B = type { %A }   ; struct B { A a; };
%C = type { %B }   ; struct C { B b; };
%D = type { i16 }  ; struct D { short s; };

; int vs. A::i  =>  MayAlias.
define i32 @f1(ptr %i, ptr %a) {
entry:
; CHECK-LABEL: f1
; CHECK: MayAlias: store i32 7, {{.*}} <-> store i32 5,
; OPT-LABEL: f1
; OPT: store i32 5,
; OPT: store i32 7,
; OPT: %[[RET:.*]] = load i32,
; OPT: ret i32 %[[RET]]
  store i32 5, ptr %i, align 4, !tbaa !3  ; TAG_int
  store i32 7, ptr %a, align 4, !tbaa !5  ; TAG_A_i
  %0 = load i32, ptr %i, align 4, !tbaa !3  ; TAG_int
  ret i32 %0
}

; int vs. B::a  =>  MayAlias.
define i32 @f2(ptr %i, ptr %b) {
entry:
; CHECK-LABEL: f2
; CHECK: MayAlias: store i32 7, {{.*}} <-> store i32 5,
; OPT-LABEL: f2
; OPT: store i32 5,
; OPT: store i32 7,
; OPT: %[[RET:.*]] = load i32,
; OPT: ret i32 %[[RET]]
  store i32 5, ptr %i, align 4, !tbaa !3  ; TAG_int
  store i32 7, ptr %b, align 4, !tbaa !7  ; TAG_B_a
  %0 = load i32, ptr %i, align 4, !tbaa !3  ; TAG_int
  ret i32 %0
}

; int vs. C::b  =>  MayAlias.
define i32 @f3(ptr %i, ptr %c) {
entry:
; CHECK-LABEL: f3
; CHECK: MayAlias: store i32 7, {{.*}} <-> store i32 5,
; OPT-LABEL: f3
; OPT: store i32 5,
; OPT: store i32 7,
; OPT: %[[RET:.*]] = load i32,
; OPT: ret i32 %[[RET]]
  store i32 5, ptr %i, align 4, !tbaa !3  ; TAG_int
  store i32 7, ptr %c, align 4, !tbaa !9  ; TAG_C_b
  %0 = load i32, ptr %i, align 4, !tbaa !3  ; TAG_int
  ret i32 %0
}

; A vs. C::b  =>  MayAlias.
define i32 @f4(ptr %a, ptr %c) {
entry:
; CHECK-LABEL: f4
; CHECK: MayAlias: store i32 7, {{.*}} <-> store i32 5,
; OPT-LABEL: f4
; OPT: store i32 5,
; OPT: store i32 7,
; OPT: %[[RET:.*]] = load i32,
; OPT: ret i32 %[[RET]]
  store i32 5, ptr %a, align 4, !tbaa !10   ; TAG_A
  store i32 7, ptr %c, align 4, !tbaa !9   ; TAG_C_b
  %0 = load i32, ptr %a, align 4, !tbaa !10  ; TAG_A
  ret i32 %0
}

; short vs. C::b  =>  NoAlias.
define i32 @f5(ptr %i, ptr %c) {
entry:
; CHECK-LABEL: f5
; CHECK: NoAlias: store i32 7, {{.*}} <-> store i32 5,
; OPT-LABEL: f5
; OPT: store i32 5,
; OPT: store i32 7,
; OPT: ret i32 5
  store i32 5, ptr %i, align 4, !tbaa !12  ; TAG_short
  store i32 7, ptr %c, align 4, !tbaa !9  ; TAG_C_b
  %0 = load i32, ptr %i, align 4, !tbaa !12  ; TAG_short
  ret i32 %0
}

; C vs. D  =>  NoAlias.
define i32 @f6(ptr %c, ptr %d) {
entry:
; CHECK-LABEL: f6
; CHECK: NoAlias: store i16 7, {{.*}} <-> store i32 5,
; OPT-LABEL: f6
; OPT: store i32 5,
; OPT: store i16 7,
; OPT: ret i32 5
  store i32 5, ptr %c, align 4, !tbaa !13  ; TAG_C
  store i16 7, ptr %d, align 4, !tbaa !15  ; TAG_D
  %0 = load i32, ptr %c, align 4, !tbaa !13  ; TAG_C
  ret i32 %0
}

; A vs. A::j  =>  MayAlias.
; This differs from A vs. A::i case in that the offsets of the final
; accessed objects in A do not match.
define i32 @f7(ptr %i, ptr %a) {
entry:
; CHECK-LABEL: f7
; CHECK: MayAlias: store i32 7, {{.*}} <-> store i32 5,
; OPT-LABEL: f7
; OPT: store i32 5,
; OPT: store i32 7,
; OPT: %[[RET:.*]] = load i32,
; OPT: ret i32 %[[RET]]
  store i32 5, ptr %i, align 4, !tbaa !10  ; TAG_A
  store i32 7, ptr %a, align 4, !tbaa !16  ; TAG_A_j
  %0 = load i32, ptr %i, align 4, !tbaa !10  ; TAG_A
  ret i32 %0
}

!0 = !{!"root"}
!1 = !{!0, i64 1, !"char"}
!2 = !{!1, i64 4, !"int"}
!3 = !{!2, !2, i64 0, i64 4}  ; TAG_int

!4 = !{!1, i64 4, !"A", !2, i64 0, i64 4, !2, i64 4, i64 4}
!5 = !{!4, !2, i64 0, i64 4}  ; TAG_A_i
!16 = !{!4, !2, i64 4, i64 4}  ; TAG_A_j

!6 = !{!1, i64 4, !"B", !4, i64 0, i64 4}
!7 = !{!6, !4, i64 0, i64 4}  ; TAG_B_a

!8 = !{!1, i64 4, !"C", !6, i64 0, i64 4}
!9 = !{!8, !6, i64 0, i64 4}  ; TAG_C_b

!10 = !{!4, !4, i64 0, i64 4}  ; TAG_A

!11 = !{!1, i64 2, !"short"}
!12 = !{!11, !11, i64 0, i64 2}  ; TAG_short

!13 = !{!8, !8, i64 0, i64 4}  ; TAG_C

!14 = !{!4, i64 2, !"D", !11, i64 0, i64 2}
!15 = !{!14, !14, i64 0, i64 2}  ; TAG_D
