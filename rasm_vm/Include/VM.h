#pragma once
#include "khash.h"
#include "Module.h"
#include "GC.h"
#include <Thread.h>
#include "Func.h"

KHASH_MAP_INIT_STR(modules, Module*)

typedef struct VM {
	khash_t(modules)* modules;
	char* root; /* directory of the entry module; module keys are relative to this */
	GC gc;
	Thread thread;
} VM;

VM* vm_new();

Module* vm_get_module(VM* vm, const char* name);
Func* vm_get_func(const Module* module, const char* name);
void vm_register(Func* func, ExternalFunc func_ptr);
void vm_free(VM* vm);
Module* vm_load(VM* vm, const char* file);
void vm_run_func(VM* vm, Func* func);