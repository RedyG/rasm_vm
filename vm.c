#include "Thread.h"
#include "Func.h"
#include <time.h>
#include <stdio.h>
#include "Disassembler.h"


int main() {
	clock_t start_time = clock();

	project_start(string_new("C:/Users/minio/source/repos/RedyLangCompiler/Sandbox/bin/Debug/net7.0/"), string_new("program.rasm"), 0);
	disassemble(program);

	double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
	printf("Done in %f seconds\n", elapsed_time);



	return 0;
}