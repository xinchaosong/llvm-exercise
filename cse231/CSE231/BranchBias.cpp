//===----------------------------------------------------------------------===//
// BranchBias.cpp
// Author: Xinchao Song
//===----------------------------------------------------------------------===//

#include "llvm/IR/CallSite.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Pass.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "branch-bias"
#define COUNT_TAKEN_FN "_Z12__countTakenPKcj"
#define COUNT_TOTAL_FN "_Z12__countTotalPKcj"
#define RESULT_FN "_Z13__printResultv"

namespace {
    struct BranchBias : public ModulePass {
        static char ID; // Pass identification, replacement for typeid
        BranchBias() : ModulePass(ID) {}

        bool runOnModule(Module &M) override {
            DenseMap<StringRef, Value *> functionNameMap;
            unsigned int blockID = 0;

            setupHookCount(M, COUNT_TAKEN_FN);
            setupHookCount(M, COUNT_TOTAL_FN);
            setupHookPrint(M);

            Module::FunctionListType &functions = M.getFunctionList();
            for (Function &F : functions) {
                StringRef functionName = F.getName();

                // Ignore any extern instrumentation functions
                if (F.getBasicBlockList().empty()) {
                    continue;
                }

                if (COUNT_TAKEN_FN == functionName || COUNT_TOTAL_FN == functionName
                    || RESULT_FN == functionName) {
                    continue;
                }

                IRBuilder<> builder(&F.front());
                functionNameMap[functionName] = builder.CreateGlobalStringPtr(functionName, functionName);

                bool isConditionalBr = false;
                unsigned int countTotal = 0;

                for (BasicBlock &bb : F) {
                    if (strcmp(bb.back().getOpcodeName(), "br") == 0 && bb.getInstList().size() > 1) {
                        Instruction *prevInstruction = bb.back().getPrevNonDebugInstruction();

                        if (isConditionalBr) {
                            Value *blockIdValue = ConstantInt::get(Type::getInt32Ty(M.getContext()), blockID);
                            InstrumentEnterCount(COUNT_TAKEN_FN, functionNameMap[functionName], blockIdValue, bb, M);
                            isConditionalBr = false;
                            countTotal++;
                            blockID++;
                        }

                        if (strcmp(prevInstruction->getOpcodeName(), "icmp") == 0) {
                            isConditionalBr = true;
                        }
                    }
                }

                Value *countTotalValue = ConstantInt::get(Type::getInt32Ty(M.getContext()), countTotal);
                InstrumentEnterCount(COUNT_TOTAL_FN, functionNameMap[functionName], countTotalValue, F.back(), M);

                if ("main" == F.getName()) {
                    InstrumentEnterPrint(F, M);
                }
            }

            return true;
        }

        static void setupHookCount(Module &M, StringRef hookName) {
            LLVMContext &Context = M.getContext();

            Type *voidTy = Type::getVoidTy(Context);
            Type *ptrTy = Type::getInt8PtrTy(Context);
            Type *intTy = Type::getInt32Ty(Context);

            FunctionType *funcTy = FunctionType::get(voidTy, {ptrTy, intTy}, false);
            Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage)->setName(hookName);
        }

        static void setupHookPrint(Module &M) {
            LLVMContext &Context = M.getContext();

            Type *voidTy = Type::getVoidTy(Context);

            FunctionType *funcTy = FunctionType::get(voidTy, {}, false);
            Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage)->setName(RESULT_FN);
        }

        static void InstrumentEnterCount(StringRef hookName, Value *functionNameValue, Value *countTotalValue,
                                         BasicBlock &blockToInstrument, Module &M) {
            LLVMContext &Context = M.getContext();

            Type *voidTy = Type::getVoidTy(Context);
            Type *ptrTy = Type::getInt8PtrTy(Context);
            Type *intTy = Type::getInt32Ty(Context);

            FunctionType *funcTy = FunctionType::get(voidTy, {ptrTy, intTy}, false);
            FunctionCallee hook = M.getOrInsertFunction(hookName, funcTy);

            Instruction *I = &blockToInstrument.back();

            CallInst::Create(hook, {functionNameValue, countTotalValue})->insertBefore(I);
        }

        static void InstrumentEnterPrint(Function &FunctionToInstrument, Module &M) {
            LLVMContext &Context = M.getContext();

            Type *voidTy = Type::getVoidTy(Context);

            FunctionType *funcTy = FunctionType::get(voidTy, {}, false);
            FunctionCallee hook = M.getOrInsertFunction(RESULT_FN, funcTy);

            BasicBlock *BB = &FunctionToInstrument.back();
            Instruction *I = &BB->back();

            CallInst::Create(hook)->insertBefore(I);
        }
    };
} // namespace

char BranchBias::ID = 0;
static RegisterPass<BranchBias>
        X("branch", "CSE 231 Part 3: Profiling Branch Bias");
