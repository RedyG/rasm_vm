#pragma once
#include <stdint.h>

typedef struct RString {
	uint32_t length;
	const char data[];
} RString;

RString* string_create(const char* str);
RString* string_from_length(uint32_t length);
RString* string_cast(uint8_t* ptr);
RString* string_concat(const RString* str1, const RString* str2);