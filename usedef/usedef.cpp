#include "llvm/IR/Function.h"
#include  "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace
{

  struct usedef: public FunctionPass
  {
      static char ID;
      usedef():FunctionPass(ID){}

      bool runOnFunction(Function &F) override{
        std:: map<std::string,int>opcode_map;
        errs() << "Hello: ";
        errs() << F.getName() << "\n";
        for(Function::iterator bb = F.begin(), e = F.end(); bb!= e; bb++)
        {
          for(auto& ins : *bb )
          {
            if(ins.getOpcode() == Instruction::Add)
            {
              for(Use& U : ins.operands()) 
              {
                Value *V = U.get();
                errs() << *V << "\n";
              }
              
            }
          }
        }
        return false;
      }
  };

}

char usedef::ID = 0;
static RegisterPass<usedef> X("usedef","This is usedef pass");
