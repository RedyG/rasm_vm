#pragma once
#include <stdint.h>
#include "value.h"

typedef struct {
	uint8_t* ip;
	Value* bp;
} Frame;