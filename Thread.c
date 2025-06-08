#include "Thread.h"
#include "Value.h"
#include "Func.h"
#include <stdlib.h>
#include <stdio.h>
#include "StackFrame.h"
#include <stdio.h>
#include <string.h>
#include "String.h"
#include "Io.h"
#include "GC.h"



#define STACK_SIZE 10024
#define STACK_FRAME_SIZE 1024

#define NEXT goto *opcodes[*ip++]

#define BIN_OP(type, name, op) {\
	type r = sp->name; \
	type l = (--sp)->name; \
	sp->name = l op r; \
	NEXT; \
}

void thread_start (Module module, uint16_t main_id) {
	void* opcodes[] = {
		&&nop, &&br, &&br_true, &&br_false, &&call, &&call_intrinsic, &&call_indirect, &&call_external, &&ret, &&ret_void, &&pop, &&dup, &&local_get, &&local_set, &&i8_const, &&i16_const, &&i32_const, &&i64_const,
		&&i32_eqz, &&i32_eq, &&i32_ne, &&i32_lt, &&u32_lt, &&i32_gt, &&u32_gt, &&i32_le, &&u32_le, &&i32_ge, &&u32_ge,   &&i64_eq, &&i64_ne, &&i64_lt, &&u64_lt,
		&&i64_gt,  &&u64_gt, &&i64_le, &&u64_le, &&i64_ge, &&u64_ge, &&f32_eq, &&f32_ne, &&f32_lt, &&f32_gt, &&f32_le, &&f32_ge, &&f64_eq, &&f64_ne, &&f64_lt, &&f64_gt,
		&&f64_le,  &&f64_ge, &&i32_add, &&i32_sub, &&i32_mul, &&i32_div, &&u32_div, &&i32_rem, &&u32_rem, &&i32_and, &&i32_or, &&i32_xor, &&i32_shl, &&i32_shr, &&u32_shr, &&i64_add,
		&&i64_sub, &&i64_mul, &&i64_div, &&u64_div, &&i64_rem, &&u64_rem, &&i64_and, &&i64_or, &&i64_xor, &&i64_shl, &&i64_shr, &&u64_shr, &&f32_add, &&f32_sub, &&f32_mul, &&f32_div,
		&&f64_add, &&f64_sub, &&f64_mul, &&f64_div, &&i8_load, &&i16_load, &&i32_load, &&i64_load,&& i8_store,&& i16_store,&& i32_store,&& i64_store, &&alloca, &&alloca_pop, &&gc_malloc,
		&&mem_cpy,&&mem_cpy_s, &&ptr_load_const
	};

	uint8_t* alloca_stack = (uint8_t*)malloc(STACK_SIZE * sizeof(uint8_t));
	uint8_t* alloca_bp = alloca_stack;
	Value* sp = (Value*)(malloc(STACK_SIZE * sizeof(Value)));
	StackFrame* frames = (StackFrame*)malloc(STACK_FRAME_SIZE * sizeof(StackFrame));

	Value* bp = sp;
	sp += module.funcs[main_id].locals_count - 1;

	uint8_t* ip = module.funcs[main_id].ip;

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
call: {
	Func func = module.funcs[*(uint16_t*)ip];
	ip += sizeof(uint16_t);

	*(++frames) = (StackFrame) { 
		.bp = bp,
		.ip = ip,
		.module = module,
		.alloca_bp = alloca_bp
	};

	module = func.module;
	bp = sp - func.args_count + 1;
	sp += func.locals_count;
	ip = func.ip;

	NEXT;
}
call_intrinsic: {
	uint16_t id = *(uint16_t*)ip;
	ip += sizeof(uint16_t);
	printf("call_intrinsic: %d\n", id);

	switch (id) {
	case 0: // break
		printf("result: %lld\n", sp->i32);
		free(alloca_bp);
		free(sp);
		free(frames);
		return;
	case 1: // print
		String* str = sp->str;
		printf(str->data);
		NEXT;
	case 2: // println
		str = sp->str;
		printf("%s\n", str->data);
		NEXT;
	case 3: // readln
		printf("call_intrinsic: %d not implemented\n", id);
		exit(1);
	case 4: // read_file
	{
		String* path = sp->str;
		String* str = read_file_to_string((const char*)path->data);
		sp->str = str;
		NEXT;
	}
	case 5: // write_file
	{
		String* str = (sp--)->str;
		String* path = (sp--)->str;
		write_string_to_file((const char*)path->data, str);
		NEXT;
	}


	case 6: // string_concat
	{
		String* str1 = (sp--)->str;
		String* str2 = sp->str;
		sp->str = string_concat(str2, str1);
		NEXT;
	}
	}
}
call_indirect: {

}
call_external: {

}
ret: {
	Value value = *sp;
	StackFrame frame = *(frames--);

	sp = bp - 1;
	*sp = value;

	module = frame.module;
	bp = frame.bp;
	ip = frame.ip;
	alloca_bp = frame.alloca_bp;


	NEXT;
}
ret_void: {
	StackFrame frame = *(frames--);

	sp = bp - 1;

	module = frame.module;
	bp = frame.bp;
	ip = frame.ip;
	alloca_bp = frame.alloca_bp;

	NEXT;
}
pop: {
	sp--;
	NEXT;
}
dup: {
	(++sp)->i64 = sp->i64;
	NEXT;
}
local_get: {
	(++sp)->i64 = bp[*(uint16_t*)ip].i64;
	printf("local_get: %lld\n", sp->i64);
	ip += sizeof(uint16_t);

	NEXT;
}
local_set: {
	bp[*(uint16_t*)ip].i64 = (sp--)->i64;
	ip += sizeof(uint16_t);

	NEXT;
}
i8_const: {
	(++sp)->i64 = *(int8_t*)ip;
	ip += sizeof(int8_t);

	NEXT;
}
i16_const: {
	(++sp)->i64 = *(int16_t*)ip;
	ip += sizeof(int16_t);

	NEXT;
}
i32_const: {
	(++sp)->i64 = *(int32_t*)ip;
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
i32_eq : BIN_OP(int32_t, i32, ==)
i32_ne : BIN_OP(int32_t, i32, !=)
i32_lt : BIN_OP(int32_t, i32, <)
u32_lt : BIN_OP(uint32_t, u32, <)
i32_gt : BIN_OP(int32_t, i32, >)
u32_gt : BIN_OP(uint32_t, u32, >)
i32_le : BIN_OP(int32_t, i32, <=)
u32_le : BIN_OP(uint32_t, u32, <=)
i32_ge : BIN_OP(int32_t, i32, >=)
u32_ge : BIN_OP(uint32_t, u32, >=)
i64_eq : BIN_OP(int64_t, i64, ==)
i64_ne : BIN_OP(int64_t, i64, !=)
i64_lt : BIN_OP(int64_t, i64, <)
u64_lt : BIN_OP(uint64_t, u64, <)
i64_gt : BIN_OP(int64_t, i64, >)
u64_gt : BIN_OP(uint64_t, u64, >)
i64_le : BIN_OP(int64_t, i64, <=)
u64_le : BIN_OP(uint64_t, u64, <=)
i64_ge : BIN_OP(int64_t, i64, >=)
u64_ge : BIN_OP(uint64_t, u64, >=)
f32_eq : BIN_OP(float, f32, ==)
f32_ne : BIN_OP(float, f32, !=)
f32_lt : BIN_OP(float, f32, <)
f32_gt : BIN_OP(float, f32, >)
f32_le : BIN_OP(float, f32, <=)
f32_ge : BIN_OP(float, f32, >=)
f64_eq : BIN_OP(double, f64, ==)
f64_ne : BIN_OP(double, f64, !=)
f64_lt : BIN_OP(double, f64, <)
f64_gt : BIN_OP(double, f64, >)
f64_le : BIN_OP(double, f64, <=)
f64_ge : BIN_OP(double, f64, >=)
i32_add: BIN_OP(int32_t, i32, +)
i32_sub: BIN_OP(int32_t, i32, -)
i32_mul: BIN_OP(int32_t, i32, *)
i32_div: BIN_OP(int32_t, i32, /)
u32_div: BIN_OP(uint32_t, u32, /)
i32_rem: BIN_OP(int32_t, i32, %)
u32_rem: BIN_OP(uint32_t, u32, %)
i32_and: BIN_OP(int32_t, i32, &)
i32_or : BIN_OP(int32_t, i32, | )
i32_xor: BIN_OP(int32_t, i32, ^)
i32_shl: BIN_OP(int32_t, i32, <<)
i32_shr: BIN_OP(int32_t, i32, >>)
u32_shr: BIN_OP(uint32_t, u32, >>)
i64_add: BIN_OP(int64_t, i64, +)
i64_sub: BIN_OP(int64_t, i64, -)
i64_mul: BIN_OP(int64_t, i64, *)
i64_div: BIN_OP(int64_t, i64, /)
u64_div: BIN_OP(uint64_t, u64, /)
i64_rem: BIN_OP(int64_t, i64, %)
u64_rem: BIN_OP(uint64_t, u64, %)
i64_and: BIN_OP(int64_t, i64, &)
i64_or : BIN_OP(int64_t, i64, |)
i64_xor: BIN_OP(int64_t, i64, ^)
i64_shl: BIN_OP(int64_t, i64, <<)
i64_shr: BIN_OP(int64_t, i64, >>)
u64_shr: BIN_OP(uint64_t, u64, >>)
f32_add: BIN_OP(float, f32, +)
f32_sub: BIN_OP(float, f32, -)
f32_mul: BIN_OP(float, f32, *)
f32_div: BIN_OP(float, f32, / )
f64_add: BIN_OP(double, f64, +)
f64_sub: BIN_OP(double, f64, -)
f64_mul: BIN_OP(double, f64, *)
f64_div: BIN_OP(double, f64, /)
i8_store: {
	int32_t offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	int8_t value = (sp--)->i32;
	*(int8_t*)(sp->ptr + offset) = value;

	NEXT;
}
i16_store: {
	int32_t offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	int16_t value = (sp--)->i32;
	*(int16_t*)(sp->ptr + offset) = value;

	NEXT;
}
i32_store: {
	int32_t offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	int32_t value = (sp--)->i32;
	*(int32_t*)(sp->ptr + offset) = value;

	NEXT;
}
i64_store: {
	int32_t offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	int64_t value = (sp--)->i64;
	*(int64_t*)(sp->ptr + offset) = value;

	NEXT;
}
i8_load: {
	int32_t offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	sp->i32 = *(int8_t*)(sp->ptr + offset);

	NEXT;
}
i16_load: {
	int32_t offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	sp->i32 = *(int16_t*)(sp->ptr + offset);

	NEXT;
}
i32_load: {
	int32_t offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	sp->i32 = *(int32_t*)(sp->ptr + offset);

	NEXT;
}
i64_load: {
	int32_t offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	sp->i64 = *(int64_t*)(sp->ptr + offset);

	NEXT;
}
alloca: {
	(++sp)->ptr = alloca_stack;
	alloca_stack += *(uint32_t*)ip;
	ip += sizeof(uint32_t);

	NEXT;
}
alloca_pop: {
	alloca_stack -= *(uint32_t*)ip;
	ip += sizeof(uint32_t);

	NEXT;
}
gc_malloc: {
	TypeInfo* type_info = sp->type_info;
	sp->ptr = gc_malloc(type_info);
	NEXT;
}
mem_cpy: {
	uint8_t* src = (sp--)->ptr;
	uint8_t* dest = (sp--)->ptr;

	int32_t dest_offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	int32_t src_offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	uint32_t size = *(uint32_t*)ip;
	ip += sizeof(uint32_t);
	memcpy(dest + dest_offset, src + src_offset, size);
}
mem_cpy_s: {
	uint8_t* src = (sp--)->ptr;
	uint8_t* dest = (sp--)->ptr;
	uint32_t size = *(uint32_t*)ip;
	ip += sizeof(uint32_t);
	memcpy(dest, src, size);

	NEXT;
}
ptr_load_const: {
	uint32_t offset = *(uint32_t*)ip;
	ip += sizeof(uint32_t);
	(++sp)->str = module.const_pool + offset;
	NEXT;
}
}