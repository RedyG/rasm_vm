#include "Thread.h"
#include "Func.h"
#include <time.h>
#include <stdio.h>
#include "Disassembler.h"
#include "VM.h"

void test() {
	printf("TESTT!!!!");
}

int main() {
	clock_t start_time = clock();

	VM* vm = vm_new();

	Module* module = vm_load(vm, "C:/Users/gagno/OneDrive/Documents/Programmation/c#/RedyLangCompiler/Sandbox/output/program.rasm");

	vm_register(vm_get_func(vm_get_module(vm, "std/io"), "test"), test);
	
	 
	disassemble(module);
	vm_run_func(vm, vm_get_func(module, "main"));

	vm_free(vm);

	double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
	printf("Done in %f seconds\n", elapsed_time);

	return 0;
}
