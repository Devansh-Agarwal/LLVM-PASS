#include "llvm/IR/Function.h"
#include  "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"


using namespace llvm;

namespace
{

  struct defuse: public FunctionPass
  {
      static char ID;
      defuse():FunctionPass(ID){}

      bool runOnFunction(Function &F) override{
        std:: map<std::string,int>opcode_map;
        errs() << "Hello: ";
        errs() << F.getName() << "\n";
        for(Function::iterator bb = F.begin(), e = F.end(); bb!= e; bb++)
        {
          for(auto& ins : *bb )
          {
            if(opcode_map.find(ins.getOpcodeName()) == opcode_map.end())
            {
              opcode_map[ins.getOpcodeName()] =1;
            } 
            else
            {
               opcode_map[ins.getOpcodeName()]+=1;
            }
          }
        }
        for(const auto& i : opcode_map)
        {
           errs() << i.first << ":::" << i.second << "\n";
        }
        opcode_map.clear();
      }
  };

}

char defuse::ID = 0;
static RegisterPass<defuse> X("defuse","This is defuse pass");
