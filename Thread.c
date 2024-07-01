#include "Thread.h"
#include "Value.h"
#include "Func.h"
#include <stdlib.h>
#include <stdio.h>

#define STACK_SIZE 10024

#define NEXT goto *opcodes[*ip++]

#define BIN_OP(type, name, op) {\
	type r = sp->name; \
	type l = (--sp)->name; \
	sp->name = l op r; \
	NEXT; \
}

void thread_start(uint8_t* program) {
	void* opcodes[] = {
		&&nop, &&br, &&br_true, &&br_false, &&exit, &&exit, &&call, &&ret, &&pop, &&local_get, &&local_set, &&i8_const, &&i16_const, &&i32_const, &&i64_const,
		&&i32_eqz, &&i32_eq, &&i32_ne, &&i32_lt, &&u32_lt, &&i32_gt, &&u32_gt, &&i32_le, &&u32_le, &&i32_ge, &&u32_ge, &&exit,   &&i64_eq, &&i64_ne, &&i64_lt, &&u64_lt,
		&&i64_gt,  &&u64_gt, &&i64_le, &&u64_le, &&i64_ge, &&u64_ge, &&f32_eq, &&f32_ne, &&f32_lt, &&f32_gt, &&f32_le, &&f32_ge, &&f64_eq, &&f64_ne, &&f64_lt, &&f64_gt,
		&&f64_le,  &&f64_ge,
	};

	program += 16; // ignore magic number and version
	Func* funcs = (Func*)program;

	// going into the first function for now
	Value* sp = (Value*)(malloc(STACK_SIZE * sizeof(Value)) - sizeof(Value));
	Value* bp = sp;
	uint8_t* ip = funcs[0].ip;



	NEXT;

nop:
	NEXT;
br: {
	ip += *(int16_t*)ip + 2;

	NEXT;
}
br_false: {
	if ((sp--)->i32 == 0)
		ip += *(int16_t*)ip;
	ip += 2;
	NEXT;
}
br_true: {
	if ((sp--)->i32)
		ip += *(int16_t*)ip;
	ip += 2;

	NEXT;
}
exit: {
	printf("result: %lld\n", sp->i64);
	free(sp);
}
call: {
	Func func = funcs[*(uint16_t*)ip];

	Value* new_bp = sp - func.args_count + 1;

	sp += func.locals_count + 1;
	sp->ip = ip + 2;
	(++sp)->bp = bp;

	bp = new_bp;

	ip = func.ip;

	NEXT;
}
ret: {
	Value value = *sp;
	Value* ret_sp = bp;
	bp = (sp - 1)->bp;
	ip = (sp - 2)->ip;
	sp = ret_sp;
	*sp = value;

	NEXT;
}
pop: {
	sp--;
	NEXT;
}
local_get: {
	(++sp)->i64 = bp[*(uint16_t*)ip].i64;
	ip += sizeof(uint16_t);

	NEXT;
}
local_set: {
	bp[*(uint16_t*)ip].i64 = (sp--)->i64;
	ip += sizeof(uint16_t);

	NEXT;
}
i8_const: {
	(++sp)->i32 = *(int8_t*)ip;
	ip += sizeof(int8_t);
}
i16_const: {
	(++sp)->i32 = *(int16_t*)ip;
	ip += sizeof(int16_t);

	NEXT;
}
i32_const: {
	(++sp)->i32 = *(int32_t*)ip;
	ip += sizeof(int32_t);

	NEXT;
}
i64_const: {
	(++sp)->i64 = *(int64_t*)ip;
	ip += sizeof(int64_t);

	NEXT;
}
i32_eqz: {
	int32_t r = sp->i32;
	int32_t l = (--sp)->i32;
	sp->i32 = l == 0;
	NEXT;
}
i32_eq: BIN_OP(int32_t, i32, ==)
i32_ne: BIN_OP(int32_t, i32, !=)
i32_lt: BIN_OP(int32_t, i32, <)
u32_lt: BIN_OP(uint32_t, u32, <)
i32_gt: BIN_OP(int32_t, i32, >)
u32_gt: BIN_OP(uint32_t, u32, >)
i32_le: BIN_OP(int32_t, i32, <=)
u32_le: BIN_OP(uint32_t, u32, <=)
i32_ge: BIN_OP(int32_t, i32, >=)
u32_ge: BIN_OP(uint32_t, u32, >=)
i64_eq: BIN_OP(int64_t, i64, ==)
i64_ne: BIN_OP(int64_t, i64, !=)
i64_lt: BIN_OP(int64_t, i64, <)
u64_lt: BIN_OP(uint64_t, u64, <)
i64_gt: BIN_OP(int64_t, i64, >)
u64_gt: BIN_OP(uint64_t, u64, >)
i64_le: BIN_OP(int64_t, i64, <=)
u64_le: BIN_OP(uint64_t, u64, <=)
i64_ge: BIN_OP(int64_t, i64, >=)
u64_ge: BIN_OP(uint64_t, u64, >=)
f32_eq: BIN_OP(float, f32, ==)
f32_ne: BIN_OP(float, f32, !=)
f32_lt: BIN_OP(float, f32, <)
f32_gt: BIN_OP(float, f32, >)
f32_le: BIN_OP(float, f32, <=)
f32_ge: BIN_OP(float, f32, >=)
f64_eq: BIN_OP(double, f64, ==)
f64_ne: BIN_OP(double, f64, !=)
f64_lt: BIN_OP(double, f64, <)
f64_gt: BIN_OP(double, f64, >)
f64_le: BIN_OP(double, f64, <=)
f64_ge: BIN_OP(double, f64, >=)



/*i64_add: {
	int64_t r = sp->i64;
	int64_t l = (--sp)->i64;
	sp->i64 = l + r;

	NEXT;
}
i64_sub: {
	int64_t r = sp->i64;
	int64_t l = (--sp)->i64;
	sp->i64 = l - r;

	NEXT;
}
i64_lt: {
	int64_t r = sp->i64;
	int64_t l = (--sp)->i64;
	sp->i32 = l < r;

	NEXT;

}*/
}