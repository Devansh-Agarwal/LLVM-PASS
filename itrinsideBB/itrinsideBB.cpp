#include "llvm/IR/Function.h"
#include  "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace
{

  struct itrinsideBB: public FunctionPass
  {
      static char ID;
      itrinsideBB():FunctionPass(ID){}

      bool runOnFunction(Function &F) override{
        errs() << "Hello: ";
        errs() << F.getName() << "\n";
        for(Function::iterator bb = F.begin(), e = F.end(); bb!= e; bb++)
        {
          errs() << "BasicBlock name = " << bb->getName() << "\n";
          errs() << "BasicBlock size = " << bb->size() << "\n";
          for(auto& ins : *bb )
          {
             errs() << "  " << ins << "\n"; 
          }
        }
      }
  };

}

char itrinsideBB::ID = 0;
static RegisterPass<itrinsideBB> X("itrinsideBB","iterate inside basic block inside a function");
