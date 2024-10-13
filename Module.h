#pragma once
#include <stdint.h>

typedef struct Func Func;

typedef struct Module {
	uint16_t imports_count;
	uint16_t funcs_count;

	Func *funcs;
} Module;

Module parse_module(const char* path);
Module get_module(const char* path);