//===----------------------------------------------------------------------===//
// CountDynamicInstructions.cpp
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

#define DEBUG_TYPE "count-dynamic-instructions"
#define COUNT_TAKEN_FN "_Z7__countPKc"
#define RESULT_FN "_Z13__printResultv"

namespace {
    struct CountDynamicInstructions : public ModulePass {
        static char ID; // Pass identification, replacement for typeid
        CountDynamicInstructions() : ModulePass(ID) {}

        bool runOnModule(Module &M) override {
            DenseMap<StringRef, Value *> opcodeNameMap;
            setupHookCount(M);
            setupHookPrint(M);

            Module::FunctionListType &functions = M.getFunctionList();
            for (Function &F : functions) {
                // Ignore our instrumentation function
                if (COUNT_TAKEN_FN == F.getName() || RESULT_FN == F.getName()) {
                    continue;
                }

                for (BasicBlock &bb : F) {
                    std::vector<StringRef> opcodeNameVec;

                    for (Instruction &i : bb) {
                        opcodeNameVec.emplace_back(i.getOpcodeName());
                    }

                    for (StringRef opcodeName : opcodeNameVec) {

                        if (!opcodeNameMap.count(opcodeName)) {
                            IRBuilder<> builder(&bb);
                            opcodeNameMap[opcodeName] = builder.CreateGlobalStringPtr(opcodeName, opcodeName);
                        }

                        InstrumentEnterCount(opcodeNameMap[opcodeName], bb, M);
                    }
                }

                if ("main" == F.getName()) {
                    InstrumentEnterPrint(F, M);
                }
            }

            return true;
        }

        static void setupHookPrint(Module &M) {
            LLVMContext &Context = M.getContext();

            Type *voidTy = Type::getVoidTy(Context);

            FunctionType *funcTy = FunctionType::get(voidTy, {}, false);
            Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage)->setName(RESULT_FN);
        }

        static void setupHookCount(Module &M) {
            LLVMContext &Context = M.getContext();

            Type *voidTy = Type::getVoidTy(Context);
            Type *ptrTy = Type::getInt8PtrTy(Context);

            FunctionType *funcTy = FunctionType::get(voidTy, ptrTy, false);
            Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage)->setName(COUNT_TAKEN_FN);
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

        static void InstrumentEnterCount(Value* opcodeValue, BasicBlock &blockToInstrument, Module &M) {
            LLVMContext &Context = M.getContext();

            Type *voidTy = Type::getVoidTy(Context);
            Type *ptrTy = Type::getInt8PtrTy(Context);

            FunctionType *funcTy = FunctionType::get(voidTy, ptrTy, false);
            FunctionCallee hook = M.getOrInsertFunction(COUNT_TAKEN_FN, funcTy);

            Instruction *I = &blockToInstrument.back();

            CallInst::Create(hook, opcodeValue)->insertBefore(I);
        }
    };
} // namespace

char CountDynamicInstructions::ID = 0;
static RegisterPass<CountDynamicInstructions>
        X("dynamic", "CSE 231 Part 2: Collecting Dynamic Instruction Counts");
