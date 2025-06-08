#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct TypeInfo {
	uint32_t size;
	uint16_t refs_count;
	uint32_t refs_offset[]; // offset from the start of the object
} TypeInfo;

typedef struct GCHeader {
	bool marked;
	TypeInfo* type_info;
	struct GCHeader* next;
} GCHeader;

void* gc_malloc(TypeInfo* type_info);