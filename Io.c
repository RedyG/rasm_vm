#pragma once
#include "Io.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

String* read_file_to_string(const char* path) {
	FILE* fileptr;

	int error = fopen_s(&fileptr, path, "rb");
	if (error != 0) {
		printf("Error opening file with code %d", error);
		exit(0);
	}

	fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
	long filelen = ftell(fileptr);             // Get the current byte offset in the file
	rewind(fileptr);                      // Jump back to the beginning of the file

	String* str = string_from_length(filelen);
	fread((void*)str->data, filelen, 1, fileptr);
	fclose(fileptr);
	return str;
}

void write_string_to_file(const char* path, const String* str) {
	FILE* fileptr;

	int error = fopen_s(&fileptr, path, "wb");
	if (error != 0) {
		printf("Error opening file with code %d", error);
		exit(0);
	}

	fwrite((const void*)str->data, str->length, 1, fileptr);
	fclose(fileptr);
}