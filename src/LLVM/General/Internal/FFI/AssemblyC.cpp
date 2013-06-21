#define __STDC_LIMIT_MACROS
#include "llvm/Config/llvm-config.h"
#if LLVM_VERSION_MAJOR < 3 || (LLVM_VERSION_MAJOR == 3 && LLVM_VERSION_MINOR < 3)
#include "llvm/LLVMContext.h"
#else
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#endif
#include "llvm/Assembly/Parser.h"
#include "llvm/Assembly/PrintModulePass.h"
#include "llvm/Pass.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm-c/Core.h"

using namespace llvm;

extern "C" {

LLVMModuleRef LLVM_General_GetModuleFromAssemblyInContext(
	LLVMContextRef context,
	const char *assembly,
	SMDiagnostic *error
) {
	wrap(ParseAssemblyString(assembly, NULL, *error, *unwrap(context))); 
}

char *LLVM_General_GetModuleAssembly(LLVMModuleRef module) {
	std::string s;
	raw_string_ostream buf(s);
	ModulePass *printPass = createPrintModulePass(&buf);
	printPass->runOnModule(*unwrap(module));
	delete printPass;
	return strdup(buf.str().c_str());
}

}

