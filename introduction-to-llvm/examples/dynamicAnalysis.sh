export LLVM="$HOME/llvm-0901"
$LLVM/build/bin/opt -load $LLVM/build/lib/IntroToLLVM.so -dynamic -S hello.ll > readyToBeInstrumented.ll
$LLVM/build/bin/llvm-link readyToBeInstrumented.ll instrumentation.ll -S -o instrumentDemo.ll
$LLVM/build/bin/lli instrumentDemo.ll
