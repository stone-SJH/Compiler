; ModuleID = '2.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64"
target triple = "x86_64-pc-linux-gnu"

@a = common global [10 x i32] zeroinitializer, align 4 ; <[10 x i32]*> [#uses=0]

define i32 @main() nounwind {
  %1 = alloca i32, align 4                        ; <i32*> [#uses=3]
  %b = alloca i32, align 4                        ; <i32*> [#uses=1]
  store i32 0, i32* %1
  %2 = load i32* %b                               ; <i32> [#uses=1]
  store i32 %2, i32* %1
  %3 = load i32* %1                               ; <i32> [#uses=1]
  ret i32 %3
}
