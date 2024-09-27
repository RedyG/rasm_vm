#pragma once
#include <stdint.h>

typedef struct {
	uint16_t args_count;
	uint16_t locals_count;
	
	uint8_t* ip;
} Func;

typedef struct {
	uint16_t args_count;
	uint16_t locals_count;

	uint32_t offset;
} ProtocolFunc;