; ModuleID = 'welcome.ll'
source_filename = "welcome.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [20 x i8] c"Welcome to CSE231!\0A\00", align 1
@alloca = private unnamed_addr constant [7 x i8] c"alloca\00", align 1
@store = private unnamed_addr constant [6 x i8] c"store\00", align 1
@call = private unnamed_addr constant [5 x i8] c"call\00", align 1
@ret = private unnamed_addr constant [4 x i8] c"ret\00", align 1

; Function Attrs: noinline norecurse optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str, i64 0, i64 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @alloca, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @store, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @call, i32 0, i32 0))
  call void @_Z7__countPKc(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @ret, i32 0, i32 0))
  call void @_Z13__printResultv()
  ret i32 0
}

declare dso_local i32 @printf(i8*, ...) #1

declare void @_Z7__countPKc(i8*)

declare void @_Z13__printResultv()

attributes #0 = { noinline norecurse optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 9.0.1 "}
