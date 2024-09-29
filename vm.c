#include "Thread.h"
#include "Func.h"
#include <time.h>
#include <stdio.h>
#include "Disassembler.h"


int main() {
	clock_t start_time = clock();

	Module module = get_module("C:/Users/minio/OneDrive/Bureau/redy_test/program.rasm");

	thread_start(module, 1);
	//disassemble(program);

	double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
	printf("Done in %f seconds\n", elapsed_time);



	return 0;
}