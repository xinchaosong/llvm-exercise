source = compression
source_c = $(source).c
source_ir = $(source).ll
instrument_dynamic = ../../instrumentation/instrument_dynamic.cpp
instrument_branchbias = ../../instrumentation/instrument_branchbias.cpp

all: part1 part2 part3

# Generates IR for the code to be analyzed
$(source_ir): $(source_c)
	clang -S -emit-llvm $(source_c)

# Part 1: Collecting Static Instruction Counts
.PHONY: Part1
part1: $(source_ir)
	opt -load $(LLVM)/build/lib/CSE231.so -static $(source_ir) > /dev/null 2>$(source).static.log

# Part 2: Collecting Dynamic Instruction Counts
.PHONY: Part2
part2: $(source_ir) $(instrument_dynamic)
	clang++ -S -emit-llvm $(instrument_dynamic)
	opt -load $(LLVM)/build/lib/CSE231.so -dynamic -S $(source_ir) > dynamic_instrumented.ll
	llvm-link dynamic_instrumented.ll instrument_dynamic.ll -S -o dynamic_instrumented_run.ll
	lli dynamic_instrumented_run.ll > $(source).dynamic.log

# Part 3: Profiling Branch Bias
.PHONY: Part3
part3: $(source_ir) $(instrument_branchbias)
	clang++ -S -emit-llvm $(instrument_branchbias)
	opt -load $(LLVM)/build/lib/CSE231.so -branchbias -S $(source_ir) > branchbias_instrumented.ll
	llvm-link branchbias_instrumented.ll instrument_branchbias.ll -S -o branchbias_instrumented_run.ll
	lli branchbias_instrumented_run.ll > $(source).branchbias.log

.PHONY: clean
clean:
	rm -f *.bc *.ll *.log
