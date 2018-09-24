#include "llvm/IR/Function.h"
#include  "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace
{

  struct opcodeCounter: public FunctionPass
  {
      static char ID;
      opcodeCounter():FunctionPass(ID){}

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

char opcodeCounter::ID = 0;
static RegisterPass<opcodeCounter> X("opcodeCounter","Count number of opcode of every type");
