# LLVM-PASS
Some basic LLVM Passes  

Usefull commands ::

$ cmake llvm       -------at the root of LLVM directory

$ make -j5 opt <PassName>  -------at the root of LLVM directory   ( PassName = LLVMHello)
  
$./opt -load <location of .so file> -<passName> <IRfileName>  -------at the llvm bin directory   
