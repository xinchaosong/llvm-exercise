add_llvm_library( CSE231 MODULE
  CountStaticInstructions.cpp
  CountDynamicInstructions.cpp
  BranchBias.cpp

  PLUGIN_TOOL
  opt
  )
