//===----------------------------------------------------------------------===//
// CountStaticInstructions.cpp
// Author: Xinchao Song
//===----------------------------------------------------------------------===//

#include "llvm/IR/Function.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "count-static-instructions"

namespace {
    struct CountStaticInstructions : public ModulePass {
        static char ID; // Pass identification, replacement for typeid
        CountStaticInstructions() : ModulePass(ID) {}

        bool runOnModule(Module &M) override {
            DenseMap<StringRef, unsigned int> opcodeMap;
            unsigned int totalCount = 0;

            Module::FunctionListType &functions = M.getFunctionList();
            for (Function &F:functions) {
                for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
                    StringRef opcodeName = I->getOpcodeName();
                    totalCount++;

                    if (opcodeMap.count(opcodeName)) {
                        opcodeMap[opcodeName]++;
                    } else {
                        opcodeMap[opcodeName] = 1;
                    }
                }
            }

            // Prints the analysis results.
            for (auto &pair: opcodeMap) {
                errs() << pair.first << "\t" << pair.second << "\n";
            }
            errs() << "TOTAL\t" << totalCount << "\n";

            return false;
        }

        // We don't modify the program, so we preserve all analyses.
        void getAnalysisUsage(AnalysisUsage &AU) const override {
            AU.setPreservesAll();
        }
    };
} // namespace

char CountStaticInstructions::ID = 0;
static RegisterPass<CountStaticInstructions>
        X("static", "CSE 231 Part 1: Collecting Static Instruction Counts");
