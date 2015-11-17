; ModuleID = '6.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64"
target triple = "x86_64-pc-linux-gnu"

define i32 @main() nounwind {
  %1 = alloca i32, align 4                        ; <i32*> [#uses=3]
  %a = alloca i32, align 4                        ; <i32*> [#uses=6]
  %b = alloca i32, align 4                        ; <i32*> [#uses=2]
  store i32 0, i32* %1
  store i32 10, i32* %a
  br label %2

; <label>:2                                       ; preds = %5, %0
  %3 = load i32* %a                               ; <i32> [#uses=1]
  %4 = icmp sgt i32 %3, 0                         ; <i1> [#uses=1]
  br i1 %4, label %5, label %11

; <label>:5                                       ; preds = %2
  %6 = load i32* %a                               ; <i32> [#uses=1]
  %7 = load i32* %b                               ; <i32> [#uses=1]
  %8 = add nsw i32 %7, %6                         ; <i32> [#uses=1]
  store i32 %8, i32* %b
  %9 = load i32* %a                               ; <i32> [#uses=1]
  %10 = add nsw i32 %9, -1                        ; <i32> [#uses=1]
  store i32 %10, i32* %a
  br label %2

; <label>:11                                      ; preds = %2
  %12 = load i32* %a                              ; <i32> [#uses=1]
  store i32 %12, i32* %1
  %13 = load i32* %1                              ; <i32> [#uses=1]
  ret i32 %13
}
