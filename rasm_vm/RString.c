#include "RString.h"
#include <string.h>
#include <stdlib.h>

RString* string_create(const char* data) {
	size_t length = strlen(data);
	RString* str = (RString*)malloc(sizeof(RString) + length + 1);
	if (str == NULL)
		return NULL; // Memory allocation failed

	str->length = (uint32_t)length;
	memcpy((char*)str->data, data, length + 1);
	return str;
}

RString* string_from_length(uint32_t length) {
	RString* str = (RString*)malloc(sizeof(RString) + length + 1);
	if (str == NULL)
		return NULL; // Memory allocation failed

	str->length = length;
	memset((char*)str->data, 0, length + 1); // Initialize with null characters
	return str;

}

RString* string_cast(uint8_t* ptr) {
	uint32_t length = *(uint32_t*)ptr;

	// checking if the length matches the null-terminated string, to check if it is valid.
	if (*(ptr + sizeof(uint32_t) + length) == '\0')
		return (RString*)ptr;

	return NULL;
}

RString* string_concat(const RString* str1, const RString* str2) {
	size_t new_length = str1->length + str2->length;
	RString* new_str = (RString*)malloc(sizeof(RString) + new_length + 1);
	if (new_str == NULL)
		return NULL; // Memory allocation failed

	new_str->length = (uint32_t)new_length;
	memcpy((char*)new_str->data, str1->data, str1->length);
	memcpy((char*)new_str->data + str1->length, str2->data, str2->length + 1); // +1 to include null terminator
	return new_str;
}

