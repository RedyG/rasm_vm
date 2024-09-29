#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// TODO: unit tests

const char* get_last_slash(const char* path) {
	const char* last_slash = NULL;
	for (; *path != '\0'; path++) {
		if (*path == '/') {
			last_slash = path;
		}
	}
	return last_slash;
}

const char* concat_from_folder(const char* path, const char* end_path) {
	const char* last_slash = get_last_slash(path);
	if (last_slash == NULL) {
		printf("no slash in path");
		exit(0);
	}
	
	size_t path_len = last_slash - path + 1;
	char* new_path = (char*)malloc(path_len + strlen(end_path) + strlen(".rasm") + 1);
	strncpy(new_path, path, path_len); // TODO: use the safe _s version
	strcpy(new_path + path_len, end_path);
	strcpy(new_path + path_len + strlen(end_path), ".rasm");
	return new_path;
}