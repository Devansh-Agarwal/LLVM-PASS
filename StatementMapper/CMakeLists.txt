add_llvm_loadable_module( LLVMStatementMapper
  StatementMapper.cpp

  DEPENDS
  intrinsics_gen
  PLUGIN_TOOL
  opt
  )
