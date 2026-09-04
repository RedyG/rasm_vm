#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "kvec.h"

typedef struct VM VM;

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

typedef struct GC {
	GCHeader* head;
	GCHeader* tail;
} GC;

GCHeader* get_gc_header(void* obj);

uint32_t get_items_count(void* obj);

void* gc_malloc_array(GC* gc, TypeInfo* type_info, uint32_t items_count);

static inline void* gc_malloc(GC* gc, TypeInfo* type_info) {
	return gc_malloc_array(gc, type_info, 1);
}

void gc_collect(VM* vm);