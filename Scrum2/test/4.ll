; ModuleID = '4.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64"
target triple = "x86_64-pc-linux-gnu"

define i32 @main() nounwind {
  %1 = alloca i32, align 4                        ; <i32*> [#uses=3]
  %A = alloca i32*, align 8                       ; <i32**> [#uses=1]
  %a = alloca i32, align 4                        ; <i32*> [#uses=2]
  %b = alloca i32, align 4                        ; <i32*> [#uses=2]
  %c = alloca i32, align 4                        ; <i32*> [#uses=3]
  %Mid = alloca i32, align 4                      ; <i32*> [#uses=1]
  store i32 0, i32* %1
  store i32 4, i32* %a
  store i32 2, i32* %b
  %2 = load i32* %a                               ; <i32> [#uses=1]
  %3 = load i32* %b                               ; <i32> [#uses=1]
  %4 = add nsw i32 %2, %3                         ; <i32> [#uses=1]
  %5 = sdiv i32 %4, 2                             ; <i32> [#uses=1]
  store i32 %5, i32* %c
  %6 = load i32* %c                               ; <i32> [#uses=1]
  %7 = load i32** %A                              ; <i32*> [#uses=1]
  %8 = sext i32 %6 to i64                         ; <i64> [#uses=1]
  %9 = getelementptr inbounds i32* %7, i64 %8     ; <i32*> [#uses=1]
  %10 = load i32* %9                              ; <i32> [#uses=1]
  store i32 %10, i32* %Mid
  %11 = load i32* %c                              ; <i32> [#uses=1]
  store i32 %11, i32* %1
  %12 = load i32* %1                              ; <i32> [#uses=1]
  ret i32 %12
}
