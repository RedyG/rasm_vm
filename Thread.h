#pragma once
#include <stdio.h>
#include <stdint.h>
#include "Value.h"
#include "FrameStack.h"


#define NEXT goto *opcodes[*ip++]

#define BIN_OP(op, type, alias) \
	do { \
		type r = sp->alias; \
		type l = (--sp)->alias; \
		printf("l: %lu, r: %lu\n", l, r); \
		sp->alias = l + r; \ 
		printf("res: %lu\n", sp->alias); \
		NEXT; \
	} while (0)

#define CONST_OP(type) \
	do { \
		*++sp = *(type*)ip; \
		ip += sizeof(type); \
		printf("%d\n", *sp); \
		NEXT; \
	} while(0)

void thread_run(uint8_t* program) {
	void* opcodes[] = {
		&& U64_CONST,&& U64_ADD,&& U64_SUB,&& U64_MUL,&& U64_DIV,
		&& END
	};

	program += 8; // ignore magic number
	program += 8; // ignore version
	uint16_t main_function = *program;
	program += 2;
	uint8_t* functions_table = program;

	uint8_t* ip = functions_table[main_function];


	Value stack[256];
	Value* sp = (Value*)stack;
	Value* bp = (Value*)stack;
	FrameStack return_frames = frame_stack_new();

	NEXT; // start the loop
CALL:
	frame_stack_push(&return_frames, (Frame) { .ip = ip, .bp = bp });
	
	NEXT;

I64_CONST: do {
	int64_t value = *(int64_t*)ip;
	ip += sizeof(int64_t);
	*++sp = (Value){ .i64 = value };
} while (0);
I64_ADD:   BIN_OP(+, int64_t, i64);
I64_SUB:   BIN_OP(-, int64_t, i64);
I64_MUL:   BIN_OP(*, int64_t, i64);
I64_DIV:   BIN_OP(/, int64_t, i64);

U64_CONST: CONST_OP(uint64_t);
U64_ADD:   BIN_OP(+, uint64_t);
U64_SUB:   BIN_OP(-, uint64_t);
U64_MUL:   BIN_OP(*, uint64_t);
U64_DIV:   BIN_OP(/ , uint64_t);

I32_CONST: CONST_OP(int32_t);
I32_ADD:   BIN_OP(+, int32_t);
I32_SUB:   BIN_OP(-, int32_t);
I32_MUL:   BIN_OP(*, int32_t);
I32_DIV:   BIN_OP(/ , int32_t);

U32_CONST: CONST_OP(uint32_t);
U32_ADD:   BIN_OP(+, uint32_t);
U32_SUB:   BIN_OP(-, uint32_t);
U32_MUL:   BIN_OP(*, uint32_t);
U32_DIV:   BIN_OP(/ , uint32_t);







END:
	printf("%lu\n", *sp);
	return 0;
}