#include "Module.h"
#include "Func.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "Path.h"
#include <VM.h>


static void inspect_memory(void* ptr) {
	uint8_t* p = (uint8_t*)ptr;
	printf("Memory around %p:\n", ptr);

	// Print 10 bytes before and 10 bytes after
	for (int i = -10; i <= 10; i++) {
		uint8_t* addr = p + i;
		printf("%p: %02X", addr, *addr);

		if (addr == p)
			printf("  <-- target");

		printf("\n");
	}
}

uint8_t* read_file(const char* path) {
	FILE* fileptr;

	int error = fopen_s(&fileptr, path, "rb");
	if (error != 0) {
		printf("Error opening file with code %d", error);
		exit(0);
	}

	fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
	long filelen = ftell(fileptr);             // Get the current byte offset in the file
	rewind(fileptr);                      // Jump back to the beginning of the file

	uint8_t* buffer = (uint8_t*)malloc(filelen * sizeof(uint8_t));
	fread(buffer, filelen, 1, fileptr);
	fclose(fileptr);
	return buffer;
}

void module_free(Module* module) {
	if (module == NULL)
		return;
	if (module->funcs != NULL) {
		// Only free Funcs this module owns (locals), not imported pointers
		for (uint16_t i = 0; i < module->funcs_count; i++)
			free(module->funcs[module->imports_count + i]);
		free(module->funcs);
	}
	free(module->image);
	module->funcs = NULL;
	module->const_pool = NULL;
	module->image = NULL;
	free(module);
}

Module* parse_module(VM* vm, const char* file_path, const char* module_key) {
	(void)module_key;
	uint8_t* image = read_file(file_path);
	uint8_t* program = image;
	Module* module = calloc(1, sizeof(Module));
	module->image = image;

	program += 16; // ignore magic number and version

	module->imports_count = *(uint16_t*)program;
	program += sizeof(uint16_t);

	module->funcs_count = *(uint16_t*)program;
	program += sizeof(uint16_t);

	uint32_t reloc_table_size = *(uint32_t*)program;
	program += sizeof(uint32_t);

	module->const_pool_size = *(uint32_t*)program;
	program += sizeof(uint32_t);

	module->funcs = (Func**)malloc((module->funcs_count + module->imports_count) * sizeof(Func*));

	// imports — bytecode paths are already short keys (e.g. "std/io")
	for (int i = 0; i < module->imports_count; i++) {
		uint16_t id = *(uint16_t*)program;
		program += sizeof(uint16_t);

		uint32_t str_length = *(uint32_t*)program;
		program += sizeof(uint32_t);
		const char* import_key = (const char*)program;
		program += str_length + 1;

		module->funcs[i] = get_module(vm, import_key)->funcs[id];
	}

	// funcs
	for (int i = 0; i < module->funcs_count; i++) {
		uint8_t is_external = *(uint8_t*)program;
		program += sizeof(uint8_t);

		uint16_t args_count = *(uint16_t*)program;
		program += sizeof(uint16_t);

		uint16_t locals_count = 0;
		uint32_t size = 0, offset = 0;
		if (!is_external) {
			locals_count = *(uint16_t*)program;
			program += sizeof(uint16_t);
			size = *(uint32_t*)program;
			program += sizeof(uint32_t);
			offset = *(uint32_t*)program;
			program += sizeof(uint32_t);
		}

		uint32_t length = *(uint32_t*)program;
		program += sizeof(uint32_t);

		const char* name = (const char*)program;
		program += length + 1;

		Func* func = malloc(sizeof(Func));

		*func = (Func) {
			.args_count = args_count,
			.locals_count = locals_count,
			.ip = (uint8_t*)(uintptr_t)offset, // I temporarily store offset here; it's patched to ip later
			.size = size,
			.module = module,
			.name = name,
			.is_external = is_external
		};

		module->funcs[i + module->imports_count] = func;

	}

	uint8_t* func_bodies = program + reloc_table_size + module->const_pool_size;
	module->const_pool = (uint8_t*)(program + reloc_table_size);
	uint8_t* reloc_table_start = program;
	while (program < reloc_table_start + reloc_table_size) {
		Module* import_module;
		if (program != reloc_table_start) {
			uint32_t length = *(uint32_t*)program;
			program += sizeof(uint32_t); // str length
			const char* import_key = (const char*)program;
			program += length + 1;

			import_module = get_module(vm, import_key);
		}
		else
			import_module = module;

		uint16_t count = *(uint16_t*)program;
		program += sizeof(uint16_t);

		for (int j = 0; j < count; j++) {
			uint32_t offset = *(uint32_t*)program ; // TODO: idk why it needs a + 1 there
			program += sizeof(uint32_t);

			uint64_t const_pool_offset = *(uint64_t*)(func_bodies + offset);
			// print const pool offset
			printf("Relocating import %d at offset %d to const pool offset %llu\n", j, offset, const_pool_offset);
			inspect_memory(func_bodies + offset);
			printf("Before: %p\n", *(uint8_t**)(func_bodies + offset));
			*(uint8_t**)(func_bodies + offset) = (import_module->const_pool + const_pool_offset);
			inspect_memory(func_bodies + offset);
		}

	}

	for (int i = 0; i < module->funcs_count; i++) {
		Func* f = module->funcs[i + module->imports_count];
		if (!f->is_external)
			f->ip = func_bodies + (size_t)f->ip;
	}

	program += module->const_pool_size;
	return module;
}

Module* get_module(VM* vm, const char* module_key) {
	if (vm->modules == NULL)
		vm->modules = kh_init(modules);

	khint_t key = kh_get(modules, vm->modules, module_key);
	if (key != kh_end(vm->modules))
		return kh_value(vm->modules, key);

	if (vm->root == NULL) {
		printf("get_module: VM root not set (call vm_load with a file path first)\n");
		exit(1);
	}

	char* file_path = path_from_module_key(vm->root, module_key);
	Module* module = parse_module(vm, file_path, module_key);
	free(file_path);

	int ret;
	key = kh_put(modules, vm->modules, _strdup(module_key), &ret);
	if (ret) {
		kh_value(vm->modules, key) = module;
	}

	return module;
}
