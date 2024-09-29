#pragma once
#include <stdint.h>
#include "module.h"


typedef struct Func {
	uint16_t args_count;
	uint16_t locals_count;
	Module module;
	uint8_t* ip;
} Func;

typedef struct {
	uint16_t args_count;
	uint16_t locals_count;

	uint32_t offset;
} ProtocolFunc;