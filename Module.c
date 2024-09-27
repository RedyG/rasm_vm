#include "Module.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "khash.h"

KHASH_MAP_INIT_STR(modules, Module)

khash_t(modules)* modules_cache = NULL;

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

	module.funcs = (Func*)malloc((module.funcs_count + module.imports_count) * sizeof(Func));

	// imports
	for (int i = 0; i < module.imports_count; i++) {
		uint16_t id = *(uint16_t*)program;
		program += sizeof(uint16_t);

		const char* import_path = (const char*)program;
		program += strlen(import_path) + 1;

		module.funcs[i] = get_module(import_path).funcs[id];
	}

	// funcs
	ProtocolFunc* protocol_funcs = (ProtocolFunc*)program;
	for (int i = 0; i < module.funcs_count; i++) {
		module.funcs[i + module.imports_count] = (Func) {
			.args_count = protocol_funcs[i].args_count,
			.locals_count = protocol_funcs[i].locals_count,
			.ip = program + protocol_funcs[i].offset
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