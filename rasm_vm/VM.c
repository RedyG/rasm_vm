#include "VM.h"

VM* vm_new() {
	VM* vm = malloc(sizeof(VM));
	vm->modules = kh_init(modules);
	return vm;
}

void vm_free(VM* vm) {

}

Module vm_load(VM* vm, const char* file) {
	return get_module(vm, file);
}