; ModuleID = 'transform.c'
source_filename = "transform.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @fastWalshTransform(i16*, i16*, i16 zeroext) #0 {
  %4 = alloca i16*, align 8
  %5 = alloca i16*, align 8
  %6 = alloca i16, align 2
  %7 = alloca i16, align 2
  %8 = alloca i16, align 2
  %9 = alloca i16, align 2
  %10 = alloca i16, align 2
  %11 = alloca i16, align 2
  %12 = alloca i16, align 2
  %13 = alloca i16, align 2
  %14 = alloca i16, align 2
  %15 = alloca i16, align 2
  store i16* %0, i16** %4, align 8
  store i16* %1, i16** %5, align 8
  store i16 %2, i16* %6, align 2
  %16 = load i16, i16* %6, align 2
  %17 = zext i16 %16 to i32
  %18 = shl i32 1, %17
  %19 = trunc i32 %18 to i16
  store i16 %19, i16* %7, align 2
  store i16 0, i16* %8, align 2
  br label %20

20:                                               ; preds = %36, %3
  %21 = load i16, i16* %8, align 2
  %22 = zext i16 %21 to i32
  %23 = load i16, i16* %7, align 2
  %24 = zext i16 %23 to i32
  %25 = icmp slt i32 %22, %24
  br i1 %25, label %26, label %39

26:                                               ; preds = %20
  %27 = load i16*, i16** %5, align 8
  %28 = load i16, i16* %8, align 2
  %29 = zext i16 %28 to i64
  %30 = getelementptr inbounds i16, i16* %27, i64 %29
  %31 = load i16, i16* %30, align 2
  %32 = load i16*, i16** %4, align 8
  %33 = load i16, i16* %8, align 2
  %34 = zext i16 %33 to i64
  %35 = getelementptr inbounds i16, i16* %32, i64 %34
  store i16 %31, i16* %35, align 2
  br label %36

36:                                               ; preds = %26
  %37 = load i16, i16* %8, align 2
  %38 = add i16 %37, 1
  store i16 %38, i16* %8, align 2
  br label %20

39:                                               ; preds = %20
  %40 = load i16, i16* %7, align 2
  %41 = zext i16 %40 to i32
  %42 = ashr i32 %41, 1
  %43 = trunc i32 %42 to i16
  store i16 %43, i16* %9, align 2
  br label %44

44:                                               ; preds = %122, %39
  %45 = load i16, i16* %9, align 2
  %46 = zext i16 %45 to i32
  %47 = icmp sge i32 %46, 1
  br i1 %47, label %48, label %127

48:                                               ; preds = %44
  store i16 0, i16* %10, align 2
  br label %49

49:                                               ; preds = %113, %48
  %50 = load i16, i16* %10, align 2
  %51 = zext i16 %50 to i32
  %52 = load i16, i16* %7, align 2
  %53 = zext i16 %52 to i32
  %54 = icmp slt i32 %51, %53
  br i1 %54, label %55, label %121

55:                                               ; preds = %49
  store i16 0, i16* %11, align 2
  br label %56

56:                                               ; preds = %109, %55
  %57 = load i16, i16* %11, align 2
  %58 = zext i16 %57 to i32
  %59 = load i16, i16* %9, align 2
  %60 = zext i16 %59 to i32
  %61 = icmp slt i32 %58, %60
  br i1 %61, label %62, label %112

62:                                               ; preds = %56
  %63 = load i16, i16* %10, align 2
  %64 = zext i16 %63 to i32
  %65 = load i16, i16* %11, align 2
  %66 = zext i16 %65 to i32
  %67 = add nsw i32 %64, %66
  %68 = add nsw i32 %67, 0
  %69 = trunc i32 %68 to i16
  store i16 %69, i16* %12, align 2
  %70 = load i16, i16* %10, align 2
  %71 = zext i16 %70 to i32
  %72 = load i16, i16* %11, align 2
  %73 = zext i16 %72 to i32
  %74 = add nsw i32 %71, %73
  %75 = load i16, i16* %9, align 2
  %76 = zext i16 %75 to i32
  %77 = add nsw i32 %74, %76
  %78 = trunc i32 %77 to i16
  store i16 %78, i16* %13, align 2
  %79 = load i16*, i16** %4, align 8
  %80 = load i16, i16* %12, align 2
  %81 = zext i16 %80 to i64
  %82 = getelementptr inbounds i16, i16* %79, i64 %81
  %83 = load i16, i16* %82, align 2
  store i16 %83, i16* %14, align 2
  %84 = load i16*, i16** %4, align 8
  %85 = load i16, i16* %13, align 2
  %86 = zext i16 %85 to i64
  %87 = getelementptr inbounds i16, i16* %84, i64 %86
  %88 = load i16, i16* %87, align 2
  store i16 %88, i16* %15, align 2
  %89 = load i16, i16* %14, align 2
  %90 = zext i16 %89 to i32
  %91 = load i16, i16* %15, align 2
  %92 = zext i16 %91 to i32
  %93 = sub nsw i32 %90, %92
  %94 = trunc i32 %93 to i16
  %95 = load i16*, i16** %4, align 8
  %96 = load i16, i16* %13, align 2
  %97 = zext i16 %96 to i64
  %98 = getelementptr inbounds i16, i16* %95, i64 %97
  store i16 %94, i16* %98, align 2
  %99 = load i16, i16* %14, align 2
  %100 = zext i16 %99 to i32
  %101 = load i16, i16* %15, align 2
  %102 = zext i16 %101 to i32
  %103 = add nsw i32 %100, %102
  %104 = trunc i32 %103 to i16
  %105 = load i16*, i16** %4, align 8
  %106 = load i16, i16* %12, align 2
  %107 = zext i16 %106 to i64
  %108 = getelementptr inbounds i16, i16* %105, i64 %107
  store i16 %104, i16* %108, align 2
  br label %109

109:                                              ; preds = %62
  %110 = load i16, i16* %11, align 2
  %111 = add i16 %110, 1
  store i16 %111, i16* %11, align 2
  br label %56

112:                                              ; preds = %56
  br label %113

113:                                              ; preds = %112
  %114 = load i16, i16* %9, align 2
  %115 = zext i16 %114 to i32
  %116 = shl i32 %115, 1
  %117 = load i16, i16* %10, align 2
  %118 = zext i16 %117 to i32
  %119 = add nsw i32 %118, %116
  %120 = trunc i32 %119 to i16
  store i16 %120, i16* %10, align 2
  br label %49

121:                                              ; preds = %49
  br label %122

122:                                              ; preds = %121
  %123 = load i16, i16* %9, align 2
  %124 = zext i16 %123 to i32
  %125 = ashr i32 %124, 1
  %126 = trunc i32 %125 to i16
  store i16 %126, i16* %9, align 2
  br label %44

127:                                              ; preds = %44
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 9.0.1 "}
