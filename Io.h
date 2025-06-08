#pragma once
#include "String.h"

String* read_file_to_string(const char* path);

void write_string_to_file(const char* path, const String* str);