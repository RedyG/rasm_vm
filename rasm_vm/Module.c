#include "Module.h"
#include "Func.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "khash.h"
#include "Path.h"

KHASH_MAP_INIT_STR(modules, Module)

khash_t(modules)* modules_cache = NULL;

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

Module parse_module(const char* path) {
	uint8_t* program = read_file(path);
	Module module;

	program += 16; // ignore magic number and version

	module.imports_count = *(uint16_t*)program;
	program += sizeof(uint16_t);

	module.funcs_count = *(uint16_t*)program;
	program += sizeof(uint16_t);

	uint32_t reloc_table_size = *(uint32_t*)program;
	program += sizeof(uint32_t);

	module.const_pool_size = *(uint32_t*)program;
	program += sizeof(uint32_t);

	module.funcs = (Func*)malloc((module.funcs_count + module.imports_count) * sizeof(Func));

	// imports
	for (int i = 0; i < module.imports_count; i++) {
		uint16_t id = *(uint16_t*)program;
		program += sizeof(uint16_t);

		program += sizeof(uint32_t);
		const char* import_path = (const char*)program;
		program += strlen(import_path) + 1;
		
		const char* full_path = concat_from_folder(path, import_path);

		module.funcs[i] = get_module(full_path).funcs[id];

		free((void*)full_path);
	}

	// funcs
	ProtocolFunc* protocol_funcs = (ProtocolFunc*)program;
	program += module.funcs_count * sizeof(ProtocolFunc);

	uint8_t* func_bodies = program + reloc_table_size + module.const_pool_size;
	module.const_pool = (uint8_t*)(program + reloc_table_size);
	uint8_t* reloc_table_start = program;
	while (program < reloc_table_start + reloc_table_size) {
		Module import_module;
		if (program != reloc_table_start) {
			uint32_t length = *(uint32_t*)program;
			program += sizeof(uint32_t); // str length
			const char* import_path = (const char*)program;
			program += strlen(import_path) + 1;

			const char* full_path = concat_from_folder(path, import_path);
			import_module = get_module(full_path);

			free((void*)full_path);
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
			*(uint8_t**)(func_bodies + offset) = (import_module.const_pool + const_pool_offset);
			inspect_memory(func_bodies + offset);
		}

	}

	program += module.const_pool_size;

	for (int i = 0; i < module.funcs_count; i++) {
		module.funcs[i + module.imports_count] = (Func) {
			.args_count = protocol_funcs[i].args_count,
			.locals_count = protocol_funcs[i].locals_count,
			.ip = func_bodies + protocol_funcs[i].offset,
			.size = protocol_funcs[i].size,
			.module = module
		};
	}
	return module;
}

Module get_module(const char* path) {
	if (modules_cache == NULL)
		modules_cache = kh_init(modules);

	khint_t key = kh_get(modules, modules_cache, path);
	if (key != kh_end(modules_cache))
		return kh_value(modules_cache, key);

	Module module = parse_module(path);

	int ret;
	key = kh_put(modules, modules_cache, path, &ret);
	if (ret) {
		kh_value(modules_cache, key) = module; // Assign the module to the key
	}

	return module;
}