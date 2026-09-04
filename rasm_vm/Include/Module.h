#pragma once
#include <stdint.h>
#include "kvec.h"

typedef struct Func Func;
typedef struct VM VM;

typedef struct Module {
	uint16_t imports_count;
	uint16_t funcs_count;
	uint32_t const_pool_size;

	Func** funcs; // TODO: use arenas pretty much everywhere.
	uint8_t* const_pool;
	uint8_t* image;
} Module;

Module* parse_module(VM* vm, const char* file_path, const char* module_key);
Module* get_module(VM* vm, const char* module_key);
void module_free(Module* module);