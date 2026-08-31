#pragma once
#include "khash.h"
#include "Module.h"

KHASH_MAP_INIT_STR(modules, Module)


typedef struct VM {
	khash_t(modules)* modules;
} VM;

VM* vm_new();

void vm_free(VM* vm);
Module vm_load(VM* vm, const char* file);
