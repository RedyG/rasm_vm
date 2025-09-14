#pragma once
#include "GC.h"
#include <stdlib.h>

GCHeader* gc_list_head = NULL; // TODO: store this in the thread and not globally to enable multi threading
GCHeader* gc_list_tail = NULL;

uint32_t get_items_count(void* obj) {
	GCHeader* header = (GCHeader*)((uint8_t*)obj - sizeof(GCHeader));
	return header->items_count;
}

void* gc_malloc_array(TypeInfo* type_info, uint32_t items_count) {
	GCHeader* header = (GCHeader*)calloc(1, sizeof(GCHeader) + type_info->size * items_count);
	if (!header)
		return NULL;

	header->marked = false;
	header->type_info = type_info;
	header->next = NULL;
	header->items_count = items_count;
	if (gc_list_head == NULL) {
		// If this is the first allocation, initialize the list
		gc_list_head = header;
		gc_list_tail = header;
	} else {
		// Append to the end of the list
		gc_list_tail->next = header;
		gc_list_tail = header;
	}

	// Return a pointer to the object part of the allocated memory
	return (void*)(header + 1);
}

static void mark(uint8_t* ptr) {
	GCHeader* header = (GCHeader*)(ptr - sizeof(GCHeader));
	if (header->marked)
		return; // Already marked
	header->marked = true;

	// Recursively mark all referenced objects
	for (uint32_t item_i = 0; item_i < header->items_count; item_i++) {
		for (uint32_t ref_i = 0; ref_i < header->type_info->refs_count; ref_i++) {
			uint32_t offset = header->type_info->refs_offset[ref_i];
			uint8_t** ref_slot = (uint8_t**)(ptr + (item_i * header->type_info->size) + offset);
			uint8_t* ref_ptr = *ref_slot;
			if (ref_ptr != NULL) {
				mark(ref_ptr);
			}
		}
	}
}

static void mark_roots(GCRefVec gc_refs) {
	for (size_t i = 0; i < kv_size(gc_refs); i++) {
		uint8_t* ptr = kv_A(gc_refs, i);
		mark(ptr);
	}
}

static void sweep() {
	GCHeader* current = gc_list_head;
	GCHeader* prev = NULL;

	while (current != NULL) {
		if (!current->marked) {
			// Unmarked object, free it
			if (prev == NULL) {
				// This is the head of the list
				gc_list_head = current->next;
			} else {
				prev->next = current->next;
			}

			if (current == gc_list_tail) {
				gc_list_tail = prev; // Update tail if we removed the last element
			}
			free(current);
			current = (prev == NULL) ? gc_list_head : prev->next; // Move to next element
		}
		else {
			// Marked object, reset mark and move to next
			current->marked = false;
			prev = current;
			current = current->next;
		}
	}
}

void gc_collect(GCRefVec gc_refs) {
	mark_roots(gc_refs);
	sweep();
}
