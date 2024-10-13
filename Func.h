#pragma once
#include <stdint.h>
#include "module.h"


typedef struct Func {
	uint8_t* ip;
	uint32_t size;
	Module module;
	uint16_t args_count;
	uint16_t locals_count;
} Func;

typedef struct {
	uint16_t args_count;
	uint16_t locals_count;

	uint32_t size;
	uint32_t offset;
} ProtocolFunc;