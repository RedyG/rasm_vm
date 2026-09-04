#pragma once
#include <stdint.h>
#include "Module.h"
#include "Value.h"
#include "GC.h"

typedef struct StackFrame
{
	uint8_t* ip;
	uint8_t* alloca_bp;
	Value* bp;
	Module* module;
	uint32_t gc_refs_size;
} StackFrame;

typedef struct Thread {
	uint8_t* alloca_stack;
	Value* sp;
	StackFrame* frames;
	GCRefVec gc_refs;
} Thread;

Thread thread_new();