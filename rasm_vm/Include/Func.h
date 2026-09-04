#pragma once
#include <stdint.h>
#include "Module.h"

typedef void (*ExternalFunc)(void);

typedef struct Func {
	uint8_t is_external;
	uint16_t args_count;
	Module* module;
	const char* name;
	union {
		struct {
			uint8_t* ip;
			uint32_t size;
			uint16_t locals_count;
		};
		ExternalFunc external_func;
	};
} Func;

typedef struct {
	uint16_t locals_count;
	uint32_t size;
	uint32_t offset;
} ProtocolFuncBody;