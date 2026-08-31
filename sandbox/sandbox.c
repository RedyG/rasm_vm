#include "Thread.h"
#include "Func.h"
#include <time.h>
#include <stdio.h>
#include "Disassembler.h"

int main() {
	clock_t start_time = clock();

	Module module = get_module("C:/Users/gagno/OneDrive/Documents/Programmation/c#/RedyLangCompiler/Sandbox/output/program.rasm");

	disassemble(module);
	thread_start(module, 2);

	double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
	printf("Done in %f seconds\n", elapsed_time);

	return 0;
}
