; ModuleID = 'gcd.ll'
source_filename = "gcd.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@alloca = private unnamed_addr constant [7 x i8] c"alloca\00", align 1
@store = private unnamed_addr constant [6 x i8] c"store\00", align 1
@load = private unnamed_addr constant [5 x i8] c"load\00", align 1
@icmp = private unnamed_addr constant [5 x i8] c"icmp\00", align 1
@br = private unnamed_addr constant [3 x i8] c"br\00", align 1
@urem = private unnamed_addr constant [5 x i8] c"urem\00", align 1
@call = private unnamed_addr constant [5 x i8] c"call\00", align 1
@phi = private unnamed_addr constant [4 x i8] c"phi\00", align 1
@ret = private unnamed_addr constant [4 x i8] c"ret\00", align 1

; Function Attrs: noinline optnone uwtable
define dso_local i32 @_Z3gcdjj(i32, i32) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %4, align 4
  %6 = icmp eq i32 %5, 0
  call void @_Z7__countPKc(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @alloca, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @alloca, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @store, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @store, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @load, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @icmp, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @br, i32 0, i32 0))
  br i1 %6, label %7, label %9

7:                                                ; preds = %2
  %8 = load i32, i32* %3, align 4
  call void @_Z7__countPKc(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @load, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @br, i32 0, i32 0))
  br label %15

9:                                                ; preds = %2
  %10 = load i32, i32* %4, align 4
  %11 = load i32, i32* %3, align 4
  %12 = load i32, i32* %4, align 4
  %13 = urem i32 %11, %12
  %14 = call i32 @_Z3gcdjj(i32 %10, i32 %13)
  call void @_Z7__countPKc(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @load, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @load, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @load, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @urem, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @call, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @br, i32 0, i32 0))
  br label %15

15:                                               ; preds = %9, %7
  %16 = phi i32 [ %8, %7 ], [ %14, %9 ]
  call void @_Z7__countPKc(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @phi, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @ret, i32 0, i32 0))
  ret i32 %16
}

; Function Attrs: noinline norecurse optnone uwtable
define dso_local i32 @main() #1 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 @_Z3gcdjj(i32 72, i32 32)
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 %2)
  call void @_Z7__countPKc(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @alloca, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @store, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @call, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @call, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @ret, i32 0, i32 0))
  call void @_Z13__printResultv()
  ret i32 0
}

declare dso_local i32 @printf(i8*, ...) #2

declare void @_Z7__countPKc(i8*)

declare void @_Z13__printResultv()

attributes #0 = { noinline optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline norecurse optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 9.0.1 "}
