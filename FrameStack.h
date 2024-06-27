#pragma once
#include "Frame.h"
#include <stdlib.h>

typedef struct {
	Frame* data;
	uintptr_t length;
	uintptr_t capacity;
} FrameStack;

FrameStack frame_stack_new() {
	return (FrameStack) {
		.data = malloc(256 * sizeof(Frame)),
		.capacity = 256
	};
}

void frame_stack_push(FrameStack* frame_stack, Frame frame) {
	if (frame_stack->length == frame_stack->capacity) {
		frame_stack->capacity *= 1.5;
		frame_stack->data = realloc(frame_stack->data, frame_stack->capacity * sizeof(Frame));
	}

	frame_stack->data[++frame_stack->length] = frame;
}

Frame frame_stack_pop(FrameStack* frame_stack) {
	return frame_stack->data[frame_stack->length--];
}

Frame frame_stack_peek(FrameStack* frame_stack) {
	return frame_stack->data[frame_stack->length];
}