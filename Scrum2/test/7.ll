; ModuleID = '7.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64"
target triple = "x86_64-pc-linux-gnu"

@main.c = internal constant [10 x i8] c"%d  \00\00\00\00\00\00", align 1 ; <[10 x i8]*> [#uses=1]

define i32 @main() nounwind {
  %1 = alloca i32, align 4                        ; <i32*> [#uses=3]
  %c = alloca [10 x i8], align 1                  ; <[10 x i8]*> [#uses=1]
  store i32 0, i32* %1
  %2 = bitcast [10 x i8]* %c to i8*               ; <i8*> [#uses=1]
  call void @llvm.memcpy.i64(i8* %2, i8* getelementptr inbounds ([10 x i8]* @main.c, i32 0, i32 0), i64 10, i32 1)
  store i32 0, i32* %1
  %3 = load i32* %1                               ; <i32> [#uses=1]
  ret i32 %3
}

declare void @llvm.memcpy.i64(i8* nocapture, i8* nocapture, i64, i32) nounwind
