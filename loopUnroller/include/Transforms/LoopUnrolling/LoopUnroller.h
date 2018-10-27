#include "llvm/IR/DebugLoc.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/Debug.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/IR/Dominators.h"
#include <bits/stdc++.h>
#include "llvm/IR/Module.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/User.h"
#include "llvm/IR/IRPrintingPasses.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/OptBisect.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/LoopUtils.h"
#include "llvm/Transforms/Utils/UnrollLoop.h"





using namespace llvm;
using namespace std;

namespace rolling {

struct rollingTheLoop : public  FunctionPass {



static char ID;
rollingTheLoop() : FunctionPass(ID) {}

void getAnalysisUsage(AnalysisUsage &AU) const;
void getNamesInnermostLoop(string&,string&,Function &);
void storeForIncBlockInstructions(BasicBlock&,vector<Instruction*>&);
void storeForMainBodyBlockInstructions(BasicBlock&,vector<Instruction*>&,Instruction*&);
void addForMainBodyInst(vector<Instruction*>&,ValueToValueMapTy&,Instruction*&);
void addForIncBodyInst(vector<Instruction*>&,ValueToValueMapTy&,Instruction*&);

bool runOnFunction(Function &);

};



}