#include <stdio.h>

// This is the function that is called at
// the very start of the program.
// It will be called right after main.
// "dummyValue" does nothing except demonstrate
// how to pass a single argument in our pass.
void __initMain(int dummyValue){
    printf("Hello, you are running an instrumented binary.\nPerformance may vary while running an instrumented binary.\n");
    // Do more work here...
}
