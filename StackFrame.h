#pragma once
#include "Value.h"
#include <stdint.h>
#include "Module.h"

typedef struct StackFrame
{
	uint8_t* ip;
	uint8_t* alloca_bp;
	Value* bp;
	Module module;
	uint32_t gc_refs_size;
} StackFrame;