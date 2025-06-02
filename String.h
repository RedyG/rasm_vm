#pragma once
#include <stdint.h>

typedef struct String {
	uint32_t length;
	const char data[];
} String;

String* string_create(const char* str);
String* string_cast(uint8_t* ptr);
String* string_concat(const String* str1, const String* str2);