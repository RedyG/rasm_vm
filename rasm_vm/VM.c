#include "VM.h"
#include <stdio.h>
#include "Thread.h"
#include "Value.h"
#include "Func.h"
#include <stdlib.h>
#include <string.h>
#include "RString.h"
#include "Io.h"
#include "GC.h"
#include "inttypes.h"
#include "kvec.h"
#include "khash.h"
#include "Path.h"

#define NEXT goto *opcodes[*ip++]

#define BIN_OP(type, name, op) {\
	type r = thread->sp->name; \
	type l = (--thread->sp)->name; \
	thread->sp->name = l op r; \
	NEXT; \
}

#define IS_SP_REF(sp) (kv_size(gc_refs) > 0 && kv_top(gc_refs) == thread->sp->ptr)

VM* vm_new() {
	VM* vm = malloc(sizeof(VM));
	vm->modules = kh_init(modules);
	vm->root = NULL;
	vm->gc = (GC){ .head = NULL, .tail = NULL };
	vm->thread = thread_new();
	return vm;
}

void vm_free(VM* vm) {
	if (vm == NULL)
		return;

	gc_collect(vm);
	printf("result: %lld\n", vm->thread.sp->i32);
	free(vm->thread.alloca_stack);
	free(vm->thread.sp);
	free(vm->thread.frames);
	kv_destroy(vm->thread.gc_refs);

	if (vm->modules != NULL) {
		for (khint_t i = kh_begin(vm->modules); i != kh_end(vm->modules); ++i) {
			if (!kh_exist(vm->modules, i))
				continue;
			module_free(kh_value(vm->modules, i));
			free((void*)kh_key(vm->modules, i));
		}
		kh_destroy(modules, vm->modules);
	}

	free(vm->root);
	free(vm);
}

Module* vm_get_module(VM* vm, const char* name) {
	if (vm == NULL || vm->modules == NULL || name == NULL)
		return NULL;

	khint_t key = kh_get(modules, vm->modules, name);
	if (key == kh_end(vm->modules))
		return NULL;

	return kh_value(vm->modules, key);
}

Func* vm_get_func(const Module* module, const char* name) {
	if (module->funcs == NULL || name == NULL)
		return NULL;

	uint32_t count = (uint32_t)module->imports_count + (uint32_t)module->funcs_count;
	for (uint32_t i = 0; i < count; i++) {
		const char* func_name = module->funcs[i]->name;
		if (func_name != NULL && strcmp(func_name, name) == 0)
			return module->funcs[i];
	}

	return NULL;
}

void vm_register(Func* func, ExternalFunc func_ptr) {
	func->external_func = func_ptr;
}

Module* vm_load(VM* vm, const char* file) {
	if (vm->root == NULL)
		vm->root = path_dirname_dup(file);

	char* module_key = path_to_module_key(file, vm->root);

	if (vm->modules == NULL)
		vm->modules = kh_init(modules);

	khint_t key = kh_get(modules, vm->modules, module_key);
	if (key != kh_end(vm->modules)) {
		Module* module = kh_value(vm->modules, key);
		free(module_key);
		return module;
	}

	Module* module = parse_module(vm, file, module_key);

	int ret;
	key = kh_put(modules, vm->modules, module_key, &ret);
	if (ret) {
		kh_value(vm->modules, key) = module;
	} else {
		free(module_key);
	}

	return module;
}

void vm_run_func(VM* vm, Func* func) {
	void* opcodes[] = {
		&&nop, &&br, &&br_true, &&br_false, &&call, &&call_intrinsic, &&call_indirect, &&call_external, &&ret, &&ret_void, &&pop, &&dup, &&local_get, &&local_set, &&i8_const, &&i16_const, &&i32_const, &&i64_const,
		&&i32_eqz, &&i32_eq, &&i32_ne, &&i32_lt, &&u32_lt, &&i32_gt, &&u32_gt, &&i32_le, &&u32_le, &&i32_ge, &&u32_ge,   &&i64_eq, &&i64_ne, &&i64_lt, &&u64_lt,
		&&i64_gt,  &&u64_gt, &&i64_le, &&u64_le, &&i64_ge, &&u64_ge, &&f32_eq, &&f32_ne, &&f32_lt, &&f32_gt, &&f32_le, &&f32_ge, &&f64_eq, &&f64_ne, &&f64_lt, &&f64_gt,
		&&f64_le,  &&f64_ge, &&i32_add, &&i32_sub, &&i32_mul, &&i32_div, &&u32_div, &&i32_rem, &&u32_rem, &&i32_and, &&i32_or, &&i32_xor, &&i32_shl, &&i32_shr, &&u32_shr, &&i64_add,
		&&i64_sub, &&i64_mul, &&i64_div, &&u64_div, &&i64_rem, &&u64_rem, &&i64_and, &&i64_or, &&i64_xor, &&i64_shl, &&i64_shr, &&u64_shr, &&f32_add, &&f32_sub, &&f32_mul, &&f32_div,
		&&f64_add, &&f64_sub, &&f64_mul, &&f64_div, &&i8_load, &&i16_load, &&i32_load, &&i64_load,&& i8_store,&& i16_store,&& i32_store,&& i64_store, &&alloca, &&alloca_pop, &&gc_malloc,
		&&gc_malloc_arr, &&mem_cpy,&&mem_cpy_s, &&ptr_load_const, &&arr_index
	};

	Thread* thread = &vm->thread;

	Module* module = func->module;

	uint8_t* alloca_bp = thread->alloca_stack;

	Value* bp = thread->sp;
	thread->sp += func->locals_count;

	GCRefVec gc_refs;
	kv_init(gc_refs);

	uint8_t* ip = func->ip;

	NEXT;
nop:
	NEXT;
br: {
	ip += *(int16_t*)ip + 2;

	NEXT;
}
br_false: {
	if ((thread->sp--)->i32 == 0)
		ip += *(int16_t*)ip;

	ip += 2;
	NEXT;
}
br_true: {
	if ((thread->sp--)->i32)
		ip += *(int16_t*)ip;
	ip += 2;

	NEXT;
}
call: {
	Func* func = module->funcs[*(uint16_t*)ip];
	ip += sizeof(uint16_t);

	*(++thread->frames) = (StackFrame) { 
		.bp = bp,
		.ip = ip,
		.module = module,
		.alloca_bp = alloca_bp,
		.gc_refs_size = kv_size(gc_refs)
	};

	module = func->module;
	bp = thread->sp - func->args_count + 1;
	thread->sp += func->locals_count;
	ip = func->ip;

	NEXT;
}
call_intrinsic: {
	uint16_t id = *(uint16_t*)ip;
	ip += sizeof(uint16_t);
	printf("call_intrinsic: %d\n", id);

	switch (id) {
	case 0: // exit
		return;
	case 1: // print
		RString* str = thread->sp->str;
		printf(str->data);
		NEXT;
	case 2: // println
		str = thread->sp->str;
		printf("%s\n", str->data);
		NEXT;
	case 3: // readln
		printf("call_intrinsic: %d not implemented\n", id);
		exit(1);
	case 4: // read_file
	{
		RString* path = thread->sp->str;
		RString* str = read_file_to_string((const char*)path->data);
		thread->sp->str = str;
		NEXT;
	}
	case 5: // write_file
	{
		RString* str = (thread->sp--)->str;
		RString* path = (thread->sp--)->str;
		write_string_to_file((const char*)path->data, str);
		NEXT;
	}
	case 6:
	case 7:
		exit(0);
	case 8: // arr_len
	{
		thread->sp->u32 = get_items_count(thread->sp->ptr);
		NEXT;
	}



	case 9: // string_concat
	{
		RString* str1 = (thread->sp--)->str;
		RString* str2 = thread->sp->str;
		thread->sp->str = string_concat(str2, str1);
		NEXT;
	}

	case 10: // arr_copy_to
	{
		uint8_t* src = (thread->sp--)->ptr;
		uint8_t* dest = (thread->sp--)->ptr;
		GCHeader* src_header = get_gc_header(src);
		uint32_t size = src_header->items_count * src_header->type_info->size;
		memcpy(src, dest, size);
		NEXT;
	}
	case 11:
	{
		uint32_t val = (thread->sp--)->u32;
		printf("Value: %" PRIu32 "\n", val);
		NEXT;
	}

	}
}
call_indirect: {

}
call_external: {
	uint16_t id = *(uint16_t*)ip;
	ip += sizeof(uint16_t);
	module->funcs[id]->external_func();
	NEXT;
}
ret: {
	Value value = *thread->sp;
	StackFrame frame = *(thread->frames--);

	thread->sp = bp - 1;
	*thread->sp = value;

	module = frame.module;
	bp = frame.bp;
	ip = frame.ip;
	alloca_bp = frame.alloca_bp;
	bool is_ref = IS_SP_REF(sp);
	kv_set_size(gc_refs, frame.gc_refs_size); // TODO: maybe resize gc_refs instead of setting size? Because rn it will never actually shrink
	if (is_ref)
		kv_push(uint8_t*, gc_refs, thread->sp->ptr);

	NEXT;
}
ret_void: {
	StackFrame frame = *(thread->frames--);

	thread->sp = bp - 1;

	module = frame.module;
	bp = frame.bp;
	ip = frame.ip;
	alloca_bp = frame.alloca_bp;
	kv_set_size(gc_refs, frame.gc_refs_size); // TODO: maybe resize gc_refs instead of setting size? Because rn it will never actually shrink

	NEXT;
}
pop: {
	thread->sp--;
	if (kv_size(gc_refs) > 0 && kv_top(gc_refs) == thread->sp->ptr) {
		kv_pop(gc_refs);
	}
	NEXT;
}
dup: {
	(++thread->sp)->i64 = thread->sp->i64; // don't need to add it to gc_refs since it is already there once
	NEXT;
}
local_get: {
	(++thread->sp)->i64 = bp[*(uint16_t*)ip].i64;
	printf("local_get: %lld\n", thread->sp->i64);
	ip += sizeof(uint16_t);

	NEXT;
}
local_set: {
	bp[*(uint16_t*)ip].i64 = (thread->sp--)->i64;
	ip += sizeof(uint16_t);

	NEXT;
}
i8_const: {
	(++thread->sp)->i64 = *(int8_t*)ip;
	ip += sizeof(int8_t);

	NEXT;
}
i16_const: {
	(++thread->sp)->i64 = *(int16_t*)ip;
	ip += sizeof(int16_t);

	NEXT;
}
i32_const: {
	(++thread->sp)->i64 = *(int32_t*)ip;
	ip += sizeof(int32_t);

	NEXT;
}
i64_const: {
	(++thread->sp)->i64 = *(int64_t*)ip;
	ip += sizeof(int64_t);

	NEXT;
}
i32_eqz: {
	int32_t r = thread->sp->i32;
	int32_t l = (--thread->sp)->i32;
	thread->sp->i32 = l == 0;
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
	int8_t value = (thread->sp--)->i32;
	*(int8_t*)(thread->sp->ptr + offset) = value;

	NEXT;
}
i16_store: {
	int32_t offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	int16_t value = (thread->sp--)->i32;
	*(int16_t*)(thread->sp->ptr + offset) = value;

	NEXT;
}
i32_store: {
	int32_t offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	int32_t value = (thread->sp--)->i32;
	*(int32_t*)(thread->sp->ptr + offset) = value;

	NEXT;
}
i64_store: {
	int32_t offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	int64_t value = (thread->sp--)->i64;
	*(int64_t*)(thread->sp->ptr + offset) = value;

	NEXT;
}
i8_load: {
	int32_t offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	thread->sp->i32 = *(int8_t*)(thread->sp->ptr + offset);

	NEXT;
}
i16_load: {
	int32_t offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	thread->sp->i32 = *(int16_t*)(thread->sp->ptr + offset);

	NEXT;
}
i32_load: {
	int32_t offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	thread->sp->i32 = *(int32_t*)(thread->sp->ptr + offset);

	NEXT;
}
i64_load: {
	int32_t offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	thread->sp->i64 = *(int64_t*)(thread->sp->ptr + offset);

	NEXT;
}
alloca: {
	(++thread->sp)->ptr = thread->alloca_stack;
	thread->alloca_stack += *(uint32_t*)ip;
	ip += sizeof(uint32_t);

	NEXT;
}
alloca_pop: {
	thread->alloca_stack -= *(uint32_t*)ip;
	ip += sizeof(uint32_t);

	NEXT;
}
gc_malloc: {
	//gc_collect(gc_refs); // for debug purposes, remove later

	TypeInfo* type_info = thread->sp->type_info;
	thread->sp->ptr = gc_malloc(&vm->gc, type_info);
	kv_push(uint8_t*, gc_refs, thread->sp->ptr);

	//gc_collect(gc_refs);
	NEXT;
}
gc_malloc_arr: {
	//gc_collect(gc_refs); // for debug purposes, remove later

	uint32_t items_count = (thread->sp--)->i32;
	TypeInfo* type_info = thread->sp->type_info;
	thread->sp->ptr = gc_malloc_array(&vm->gc, type_info, items_count);
	kv_push(uint8_t*, gc_refs, thread->sp->ptr);

	//gc_collect(gc_refs);
	NEXT;
}
mem_cpy: {
	uint8_t* src = (thread->sp--)->ptr;
	uint8_t* dest = (thread->sp--)->ptr;

	int32_t dest_offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	int32_t src_offset = *(int32_t*)ip;
	ip += sizeof(int32_t);
	uint32_t size = *(uint32_t*)ip;
	ip += sizeof(uint32_t);
	memcpy(dest + dest_offset, src + src_offset, size);
}
mem_cpy_s: {
	uint8_t* src = (thread->sp--)->ptr;
	uint8_t* dest = (thread->sp--)->ptr;
	uint32_t size = *(uint32_t*)ip;
	ip += sizeof(uint32_t);
	memcpy(dest, src, size);

	NEXT;
}
ptr_load_const: {
	(++thread->sp)->ptr = *(uint8_t**)ip;
	ip += sizeof(uint8_t**);
	NEXT;
}
arr_index: {
	uint32_t index = (thread->sp--)->u32;
	uint8_t* arr_ptr = thread->sp->ptr;
	uint32_t item_size = get_gc_header(arr_ptr)->type_info->size;
	thread->sp->ptr = arr_ptr + (index * item_size);
	NEXT;
}
}