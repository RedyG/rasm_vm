#pragma once
#include "RString.h"

RString* read_file_to_string(const char* path);

void write_string_to_file(const char* path, const RString* str);