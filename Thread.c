#include "Thread.h"
#include "Value.h"
#include "Func.h"
#include <stdlib.h>
#include <stdio.h>

#define STACK_SIZE 10024

#define NEXT goto *opcodes[*ip++]

void thread_start(uint8_t* program) {
	void* opcodes[] = {
		&& I64_CONST, && I64_ADD, &&I64_LT, && CALL, && RET, &&LOAD_LOCAL,
		&&BR, &&BR_FALSE, &&BR_TRUE, &&END, &&I64_SUB
	};

	program += 16; // ignore magic number and version
	Func* funcs = (Func*)program;

	// going into the first function for now
	Value* sp = (Value*)(malloc(STACK_SIZE * sizeof(Value)) - sizeof(Value));
	Value* bp = sp;
	uint8_t* ip = funcs[0].ip;



	NEXT;
I64_CONST: {
	(++sp)->i64 = *(int64_t*)ip;
	ip += sizeof(int64_t);

	NEXT;
}

I64_ADD: {
	int64_t r = sp->i64;
	int64_t l = (--sp)->i64;
	sp->i64 = l + r;

	NEXT;
}
I64_SUB: {
	int64_t r = sp->i64;
	int64_t l = (--sp)->i64;
	sp->i64 = l - r;

	NEXT;
}
I64_LT: {
	int64_t r = sp->i64;
	int64_t l = (--sp)->i64;
	sp->i32 = l < r;

	NEXT;

}

CALL: {
	Func func = funcs[*(uint16_t*)ip];

	Value* new_bp = sp - func.args_count + 1;

	sp += func.locals_count + 1;
	sp->ip = ip + 2;
	(++sp)->bp = bp;

	bp = new_bp;

	ip = func.ip;

	NEXT;
}
RET: {
	Value value = *sp;
	Value* ret_sp = bp;
	bp = (sp - 1)->bp;
	ip = (sp - 2)->ip;
	sp = ret_sp;
	*sp = value;


	NEXT;

}
LOAD_LOCAL: {
	(++sp)->i64 = bp[*(uint16_t*)ip].i64;
	ip += sizeof(uint16_t);

	NEXT;
}
BR: {
	ip += *(int16_t*)ip;

	NEXT;
}
BR_FALSE: {
	if ((sp--)->i32 == 0)
		ip += *(int16_t*)ip;
	ip+= 2;
	NEXT;
}
BR_TRUE: {
	if ((sp--)->i32)
		ip += *(int16_t*)ip;
	ip += 2;

	NEXT;
}

END: {
	printf("res: %lld\n", sp->i64);
	free(sp);
}
}