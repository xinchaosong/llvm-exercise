export LLVM="$HOME/llvm-0901"
$LLVM/build/bin/opt -load $LLVM/build/lib/IntroToLLVM.so -static1 < loops.ll > /dev/null
