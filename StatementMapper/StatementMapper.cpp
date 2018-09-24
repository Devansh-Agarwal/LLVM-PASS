#include "llvm/Transforms/StatementMapper/StatementMapper.h"
/*
  function pass is used all the induction operators are not printed
*/
   void arithmeticMapping::StatementMapper::hashingInst(Instruction* temp, unsigned int number)
   {
      for(Use& U : temp->operands())
      {
        Instruction * temp1 = (Instruction*) U.get();
        std::string name = "<Invalid operator> ";
        hashingInst(temp1, number);
        if(strcmp(name.c_str(),temp1->getOpcodeName()) != 0)
        {
            if(isa<AllocaInst>(temp1))
            {
              auto check = std::find(allocainstr[number].begin(),allocainstr[number].end(),temp1);
              if(check !=  allocainstr[number].end())
              {
                allocainstr[number].erase(check);
              }
             allocainstr[number].push_back(temp1);
            }
            else
            {
              instr[number].push_back(temp1);
            }
        }
      }
   }
   bool arithmeticMapping::StatementMapper:: runOnFunction(Function &F){
        std::string store = "store";
        std::string ret = "ret";
        for(Function::iterator bb = F.begin(), e = F.end(); bb!= e; bb++)
        {
          if(bb->getName().startswith("for.inc"))
            continue;
          for(BasicBlock::iterator inst = bb->begin(), endInst = bb->end(); inst!= endInst; inst++)
          {
            if(DILocation *dloc = inst->getDebugLoc())
            {
                unsigned int line = dloc->getLine();
                if(store == inst->getOpcodeName() || ret == inst->getOpcodeName())
                {
                  hashingInst(&(*inst), line);
                  instr[line].push_back(&(*inst));
                }
            }     
          }
        }
        std::map<int,std::vector<Instruction*>> :: iterator itr1 ;
        std::map<int,std::vector<Instruction*>> :: iterator itr2 ;
        for(itr1 = instr.begin(),itr2 =allocainstr.begin(); itr1!= instr.end() && itr2!= allocainstr.end(); itr1++, itr2++ )
        {
          // while(instr[itr2->first].size()== 0)
          // {
          //     itr2++;
          // }
          std::vector<Instruction*> instruct = itr1->second;
          std::vector<Instruction*> allocinstruct = itr2->second;
          int check=0;
          for(unsigned int i =0; i < instruct.size(); i++)
          {
            if((isa<BinaryOperator>(*instruct[i])))
            {
              check=1;
            }
          }
          if(check)
          {
            dbgs()<< "Statement=" << itr1->first<<"{\n";
          for(unsigned int i =0; i < allocinstruct.size(); i++)
          {
            dbgs()<< *allocinstruct[i] << "\n";
          }
          for(unsigned int i =0; i < instruct.size(); i++)
          {
              dbgs()<< *instruct[i] << "\n";
          }

          dbgs() << "}\n";  
          }
          

        }

        return false;
      }
  
char arithmeticMapping::StatementMapper::ID = 0;
static RegisterPass<arithmeticMapping::StatementMapper> X("stmt-mapper","Assignment");
