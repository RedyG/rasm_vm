#pragma once
#include <stdint.h>
#include "RString.h"
#include "GC.h"

typedef union Value {
	uint64_t u64;
	int64_t i64;
	uint32_t u32;
	int32_t i32;
	float f32;
	double f64;

	uint8_t* ptr;
	TypeInfo* type_info;
	RString* str;
} Value;