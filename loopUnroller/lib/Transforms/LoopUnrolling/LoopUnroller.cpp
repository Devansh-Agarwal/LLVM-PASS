#include "llvm/Transforms/LoopUnrolling/LoopUnroller.h"

static cl::opt<unsigned int> uf ("unroll-factor", cl::init(4),cl::desc("Provide the unroll factor \n"));

/* 
	All the for main body blocks and all the for inc body instructions are stored in 
	seperate vectors and these instructions are added in the begining of the for main body block
	and the leftover is added as an epilogue in the for end block.

*/
void  rolling::rollingTheLoop::getAnalysisUsage(AnalysisUsage &AU) const {
	AU.addRequired<LoopInfoWrapperPass>();
	AU.addPreserved<LoopInfoWrapperPass>();
}

// This function gets the name of the innermost for main body block and cond block 
void rolling::rollingTheLoop::getNamesInnermostLoop(string& forMainBodyname,string&conditionBlockName,Function &F)
{
	for (Function::iterator bb = F.begin(), e = F.end(); bb!= e; bb++) 
	{
		if((bb->getName()).startswith("for.cond"))
		{
			conditionBlockName = bb->getName();
		}
		if((bb->getName()).startswith("for.body"))
		{
			
			forMainBodyname = bb->getName();
		}

	}
}
// This function stores all the for inc block instructions in a vector
void rolling::rollingTheLoop::storeForIncBlockInstructions(BasicBlock& BB,vector<Instruction*>&forIncBodyInstructionsructions)
{
		
	for (BasicBlock::iterator I = BB.begin(), e = BB.end(); I!= e; I++)
	{
		if(I->getOpcode() == 2)
		{
			continue;
		}
		forIncBodyInstructionsructions.push_back(&(*I));
	}
}
// This function stores all the for body block instructions in a vector and also gets the 1st instruction of the block
void rolling::rollingTheLoop::storeForMainBodyBlockInstructions(BasicBlock& BB,vector<Instruction*>&forMainBodyInstructions,Instruction*& forBody1stInstPtr)
{
		forBody1stInstPtr =&(*BB.begin());
		for(BasicBlock::iterator i = BB.begin(), e = BB.end(); i != e; ++i)
		{
			if(&(*i) == BB.getTerminator())continue;
			forMainBodyInstructions.push_back(&(*i));

		}
}

// adds the for body block instructions in any block, used for for body and for end block
void rolling::rollingTheLoop::addForMainBodyInst(vector<Instruction*>&forMainBodyInstructions,ValueToValueMapTy& vmapForMainBody,Instruction*&forBody1stInstPtr)
{
	for(unsigned int j=0;j<forMainBodyInstructions.size();j++)
	{
		auto *new_inst = forMainBodyInstructions[j]->clone();

		new_inst->insertBefore(forBody1stInstPtr);

		vmapForMainBody[forMainBodyInstructions[j]] = new_inst;

		RemapInstruction(new_inst, vmapForMainBody, RF_NoModuleLevelChanges | RF_IgnoreMissingLocals);
	}
}
// adds the for inc block instructions in any block, used for for body and for end block
void rolling::rollingTheLoop::addForIncBodyInst(vector<Instruction*>&forIncBodyInstructions,ValueToValueMapTy& vmapForIncBody,Instruction*&forBody1stInstPtr)
{
	for(unsigned int j=0;j<forIncBodyInstructions.size();j++)
	{
		auto *new_inst1 = forIncBodyInstructions[j]->clone();

		new_inst1->insertBefore(forBody1stInstPtr);

		vmapForIncBody[forIncBodyInstructions[j]] = new_inst1;

		RemapInstruction(new_inst1, vmapForIncBody, RF_NoModuleLevelChanges | RF_IgnoreMissingLocals);
	}
}
bool  rolling::rollingTheLoop::runOnFunction(Function &F) 
{

	// vectors for storing all the instructions 	
	vector<Instruction*> forMainBodyInstructions,forIncBodyInstructions;

	ValueToValueMapTy vmapForMainBody;
	ValueToValueMapTy vmapForIncBody;
	
	// pointers to 1st instructions of body and end block
	Instruction* forBody1stInstPtr,*endBl;
	
	// how many loop iterations are left for epilogue
	int epilogueVAl;	
	
	string forMainBodyname,conditionBlockName,forEndBlock = "for.end",opcodeCmp ="icmp";
	
	getNamesInnermostLoop(forMainBodyname,conditionBlockName,F);
	

	for (BasicBlock &BB : F) 
	{
		

		if(BB.getName() == conditionBlockName)
		{
			
			for(Instruction &I : BB)
			{
				if(I.getOpcodeName() == opcodeCmp)
				{
					
					Value* op2 = I.getOperand(1);
					
					ConstantInt* op2Val  = dyn_cast<ConstantInt>(op2);
					int op2ValINT = op2Val->getSExtValue() ;
					int temp = op2ValINT;
					// checks if uf is bigger than the value N in i<N;
					if((unsigned) temp  < uf)
					{				
						F.dump();
						return true;
					}
					epilogueVAl = op2ValINT%uf;
					

					op2ValINT = op2ValINT - (op2ValINT%uf);
					
					//	updates the condition
					Value * op2Update = ConstantInt::get(op2->getType(), op2ValINT);
					I.setOperand(1, op2Update);

				}
			}
		}

		//storing for inc instructions
		if(BB.getName() ==  "for.inc")
		{
			storeForIncBlockInstructions(BB,forIncBodyInstructions);
		}

		//storing for body instructions
		if(BB.getName().startswith(forMainBodyname))
		{
			storeForMainBodyBlockInstructions(BB,forMainBodyInstructions,forBody1stInstPtr);

		}

		//getting 1st instruction of for end block
		if(BB.getName() == forEndBlock)
		{
			 endBl = &(*(BB.begin())); 
		}

	}

	// adding instructions in the for body block
	for(unsigned int i=0;i<uf-1;i++)
	{

		addForMainBodyInst(forMainBodyInstructions,vmapForMainBody,forBody1stInstPtr);

		addForIncBodyInst(forIncBodyInstructions,vmapForIncBody,forBody1stInstPtr);


	}
		// adding instructions in the for end block

	for(int i = 0; i< epilogueVAl; i++)
	{
		addForMainBodyInst(forMainBodyInstructions,vmapForMainBody,endBl);
		addForIncBodyInst(forIncBodyInstructions,vmapForIncBody,endBl);
	
	}
	F.dump();
	return true;
}

char  rolling::rollingTheLoop::ID = 0;
static RegisterPass< rolling::rollingTheLoop> X("loop-unrolling", "Mapping the IR instructions to its source line");