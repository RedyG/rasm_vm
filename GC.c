#pragma once
#include "GC.h"
#include <stdlib.h>

GCHeader* gc_list_head = NULL; // TODO: store this in the thread and not globally to enable multi threading
GCHeader* gc_list_tail = NULL;

void* gc_malloc(TypeInfo* type_info) {
	GCHeader* header = (GCHeader*)malloc(sizeof(GCHeader) + type_info->size);
	if (!header)
		return NULL;

	header->marked = false;
	header->type_info = type_info;
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