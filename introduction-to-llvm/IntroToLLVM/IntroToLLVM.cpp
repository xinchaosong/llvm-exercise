//===----------------------------------------------------------------------===//
// IntroToLLVM.cpp
// Modified example code from "Introduction to LLVM" by Mike Shah (http://mshah.io/)
// (Original code: http://www.mshah.io/fosdem/Hello.cpp)
// Modified by Xinchao Song
//===----------------------------------------------------------------------===//

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/CallSite.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "introtollvm"

namespace {
    struct IntroToLLVM1 : public FunctionPass {
        static char ID; // Pass identification, replacement for typeid
        IntroToLLVM1() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
            unsigned int basicBlockCount = 0;
            unsigned int instructionCount = 0;

            for (BasicBlock &bb : F) {
                ++basicBlockCount;

                for (Instruction &i : bb) {
                    ++instructionCount;
                }
            }

            errs() << "Function Name: ";
            errs().write_escaped(F.getName()) << ", Basic Blocks: " << basicBlockCount
                                              << ", Instruction: " << instructionCount << "\n";
            return false;
        }

        // We don't modify the program, so we preserve all analyses.
        void getAnalysisUsage(AnalysisUsage &AU) const override {
            AU.setPreservesAll();
        }
    };
}

char IntroToLLVM1::ID = 0;
static RegisterPass <IntroToLLVM1>
        X("static1", "IntroToLLVM Example for Static Analysis 1: Pass with getAnalysisUsage implemented");


namespace {
    struct IntroToLLVM2 : public FunctionPass {
        static char ID; // Pass identification, replacement for typeid
        IntroToLLVM2() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
            for (BasicBlock &bb : F) {
                for (Instruction &i : bb) {
                    // Find where callsite is of our instruction
                    CallSite cs(&i);
                    if (!cs.getInstruction()) {
                        continue;
                    }

                    Value *called = cs.getCalledValue()->stripPointerCasts();

                    if (Function * f = dyn_cast<Function>(called)) {
                        errs() << "\tDirect call to function:" << f->getName()
                               << " from " << F.getName() << "\n";
                    }
                }
            }

            return false;
        }

        // We don't modify the program, so we preserve all analyses.
        void getAnalysisUsage(AnalysisUsage &AU) const override {
            AU.setPreservesAll();
        }
    };
}

char IntroToLLVM2::ID = 0;
static RegisterPass <IntroToLLVM2>
        Y("static2", "IntroToLLVM Example for Static Analysis 2: Get direct calls");


namespace {
    struct IntroToLLVM3 : public ModulePass {
        static char ID; // Pass identification, replacement for typeid
        IntroToLLVM3() : ModulePass(ID) {}

        bool runOnModule(Module &M) override {
            // Setup hooks
            // Create a little stub function
            setupHooks("_Z10__initMaini", M);

            // Loop through all of our functions in the module
            // This is where you could do something intersesting like only
            // modify a subset of the functions
            // The key is not to modify instrumenting functions!
            Module::FunctionListType &functions = M.getFunctionList();

            for (Module::FunctionListType::iterator FI = functions.begin(), FE = functions.end(); FI != FE; ++FI) {
                // Ignore our instrumentation function
                if ("_Z10__initMaini" == FI->getName()) {
                    continue;
                }

                if ("main" == FI->getName()) {
                    InstrumentEnterFunction("_Z10__initMaini", *FI, M);
                }
            }

            return true;
        }

        // This creates a prototype of the function, so that LLVM knows about it
        // when we are hooking the function into a .ll file.
        //
        // Because we instrument a .ll file before attaching our actually instrumentation files (a separate .ll)
        // we need to have the function signature ready to go. (One problem is LLVM creates arguments lazily, so we
        // would not know about them, but by doing this we avoid that problem.)
        static void setupHooks(StringRef InstrumentingFunctionName, Module &M) {
            LLVMContext &Context = M.getContext();

            Type *voidTy = Type::getVoidTy(Context);
            Type *intTy = Type::getInt32Ty(Context);

            // Specify the return value, arguments, and if there are variable number of arguments.
            FunctionType *funcTy = FunctionType::get(voidTy, intTy, false);
            Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage)->setName(InstrumentingFunctionName);

        }

        static void
        InstrumentEnterFunction(StringRef InstrumentingFunctionName, Function &FunctionToInstrument, Module &M) {
            // Create the actual function
            // If we have a function already, then the below is very useful
            //
            // FunctionType* funcTy = M.getFunction(InstrumentingFunctionName)->getFunctionType();
            //
            // However, we are hooking into a function that we will merge later, so we instead build our function type
            // Both methods will allow us to then modify the function arguments.
            //
            // Build out the function type
            LLVMContext &Context = M.getContext();
            // The functions return type
            Type *voidTy = Type::getVoidTy(Context);
            // The start of our parameters
            Type *intTy = Type::getInt32Ty(Context);
            // push back all of the parameters
            std::vector < llvm::Type * > params;
            params.push_back(intTy);
            // Specify the return value, arguments, and if there are variable numbers of arguments.
            FunctionType *funcTy = FunctionType::get(voidTy, params, false);
            // Create a Constant that grabs our function
            FunctionCallee hook = M.getOrInsertFunction(InstrumentingFunctionName, funcTy);

            // We determine where we want to add our instrumentation.
            // In this instance, we want to instrument the first basic block, and
            // put the instruction at the front. Every function has at least an entry:
            // block in the LLVM IR, so this should be valid.
            BasicBlock *BB = &FunctionToInstrument.front();
            Instruction *I = &BB->front();

            // In order to set the arguments of the instrumenting function, we are going to
            // get all of our instrumenting functions arguments, and then modify them.
            std::vector < Value * > args;

            for (unsigned int i = 0; i < funcTy->getNumParams(); ++i) {
                Type *t = funcTy->getParamType(i);
                // We get the argument, and then we can re-assign its value
                // In this case, we are looking at our obController to see the function name in the hashmap, and then its value
                Value *newValue = ConstantInt::get(t, 0x1234);
                args.push_back(newValue);
            }

            // Create our function call
            CallInst::Create(hook, args)->insertBefore(I);
        }
    };
}

char IntroToLLVM3::ID = 0;
static RegisterPass <IntroToLLVM3>
        Z("dynamic", "IntroToLLVM Example for Dynamic Analysis: Code injection");
