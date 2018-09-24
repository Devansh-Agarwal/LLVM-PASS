#include "llvm/IR/Function.h"
#include  "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace
{

  struct MyHello: public FunctionPass
  {
      static char ID;
      MyHello():FunctionPass(ID){}

      bool runOnFunction(Function &F) override{
        errs() << "Hello: ";
        errs() << F.getName() << "\n";
      }
  };

}

char MyHello::ID = 0;
static RegisterPass<MyHello> X("myhello","Hello world pass");
