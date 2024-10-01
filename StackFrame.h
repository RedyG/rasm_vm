#pragma once
#include "Value.h"
#include <stdint.h>
#include "Module.h"

typedef struct StackFrame
{
	uint8_t* ip;
	Value* bp;
	Module module;
} StackFrame;