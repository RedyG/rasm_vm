#include "Thread.h"
#include "Func.h"
#include <time.h>
#include <stdio.h>

uint8_t main_func[] = {
	0, 10, 0, 0, 0, 0, 0, 0, 0, // push 10
	3, 1, 0, // call fib
	9, // end
};

uint8_t fib[] = {
	5, 0, 0, // load arg 0
	0, 2, 0, 0, 0, 0, 0, 0, 0, // push 2
	2, // lt
	7, 4, 0, // branch if false by 4 ( jump over 4 bytes )


	5, 0, 0, // load arg 0
	4, // ret


	5, 0, 0, // load arg 0
	0, 1, 0, 0, 0, 0, 0, 0, 0, // push 1
	10, // sub
	3, 1, 0, // call fib

	5, 0, 0, // load arg 0
	0, 2, 0, 0, 0, 0, 0, 0, 0, // push 2
	10, // sub 
	3, 1, 0, // call fib

	1, // add

	4, // ret
};

int main() {
	Func funcs[] = {
		(Func) {
			.args_count = 0,
			.ip = main_func,
			.locals_count = 0
		},
		(Func) {
			.args_count = 1,
			.ip = fib,
			.locals_count = 0
		}
	};


	uint8_t* program = (uint8_t*)funcs;

	clock_t start_time = clock();

	thread_start(program - 16);

	double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
	printf("Done in %f seconds\n", elapsed_time);



	return 0;
}