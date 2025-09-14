#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "kvec.h"

typedef kvec_t(uint8_t*) GCRefVec;

typedef struct TypeInfo {
	uint32_t size;
	uint32_t refs_count;
	uint32_t refs_offset[]; // offset from the start of the object
} TypeInfo;

typedef struct GCHeader {
	bool marked;
	uint32_t items_count; // 1 by default, otherwise its an array
	TypeInfo* type_info;
	struct GCHeader* next;
} GCHeader;

uint32_t get_items_count(void* obj);

void* gc_malloc_array(TypeInfo* type_info, uint32_t items_count);

void* gc_malloc(TypeInfo* type_info) {
	return gc_malloc_array(type_info, 1);
}

void gc_collect(GCRefVec gc_refs);