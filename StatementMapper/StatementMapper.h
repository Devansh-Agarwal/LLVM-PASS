#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/Support/Debug.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/User.h"
#include "bits/stdc++.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"

/*
two maps are used one saves the alloca instructions and the other stores the 
other instrunctions.

*/
using namespace llvm;
namespace arithmeticMapping
{
 
    struct StatementMapper : public FunctionPass{
        
    std::map<int,std::vector<Instruction*>> instr;
    std::map<int,std::vector<Instruction*>> allocainstr;
          static char ID;
          StatementMapper() :FunctionPass(ID){}
          void hashingInst(Instruction* temp, unsigned int number);
          bool runOnFunction(Function &F);
    };    
}
