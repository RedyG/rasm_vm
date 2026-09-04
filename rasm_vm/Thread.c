#include "Thread.h"
#include "Value.h"
#include "Func.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Io.h"
#include "GC.h"
#include "inttypes.h"
#include "VM.h"
#include "kvec.h"


#define STACK_SIZE 10024
#define STACK_FRAME_SIZE 1024


Thread thread_new() {
	GCRefVec gc_refs;
	kv_init(gc_refs);

	return (Thread) {
		.alloca_stack = (uint8_t*)malloc(STACK_SIZE * sizeof(uint8_t)),
		.sp = (Value*)(malloc(STACK_SIZE * sizeof(Value))),
		.frames = (StackFrame*)malloc(STACK_FRAME_SIZE * sizeof(StackFrame)),
		.gc_refs = gc_refs
	};
}