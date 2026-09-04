#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// TODO: unit tests

static inline bool path_is_sep(char c) {
	return c == '/' || c == '\\';
}

static inline const char* get_last_slash(const char* path) {
	const char* last_slash = NULL;
	for (; *path != '\0'; path++) {
		if (path_is_sep(*path))
			last_slash = path;
	}
	return last_slash;
}

static inline void path_normalize_slashes(char* path) {
	for (char* p = path; *p; p++) {
		if (*p == '\\')
			*p = '/';
	}
}

/* Directory of path, no trailing slash. Caller frees. */
static inline char* path_dirname_dup(const char* path) {
	const char* last_slash = get_last_slash(path);
	if (last_slash == NULL)
		return _strdup(".");

	size_t len = (size_t)(last_slash - path);
	if (len == 0)
		len = 1; /* e.g. "/file" */

	char* dir = (char*)malloc(len + 1);
	memcpy(dir, path, len);
	dir[len] = '\0';
	path_normalize_slashes(dir);
	return dir;
}

/* Strip a trailing ".rasm" if present (case-sensitive). */
static inline void path_strip_rasm_ext(char* path) {
	size_t len = strlen(path);
	if (len >= 5 && strcmp(path + len - 5, ".rasm") == 0)
		path[len - 5] = '\0';
}

/*
 * Module cache key for a filesystem path relative to root.
 * Forward slashes, no ".rasm". Caller frees.
 */
static inline char* path_to_module_key(const char* file, const char* root) {
	char* norm_file = _strdup(file);
	path_normalize_slashes(norm_file);

	const char* rel = norm_file;
	if (root != NULL) {
		char* norm_root = _strdup(root);
		path_normalize_slashes(norm_root);
		size_t root_len = strlen(norm_root);
		if (_strnicmp(norm_file, norm_root, root_len) == 0) {
			rel = norm_file + root_len;
			while (*rel == '/')
				rel++;
		}
		free(norm_root);
	}

	char* key = _strdup(rel);
	path_strip_rasm_ext(key);
	free(norm_file);
	return key;
}

/* root + "/" + key + ".rasm". Caller frees. */
static inline char* path_from_module_key(const char* root, const char* key) {
	size_t root_len = root ? strlen(root) : 0;
	size_t key_len = strlen(key);
	char* path = (char*)malloc(root_len + 1 + key_len + 5 + 1);
	size_t n = 0;
	if (root_len > 0) {
		memcpy(path, root, root_len);
		n = root_len;
		if (!path_is_sep(path[n - 1]))
			path[n++] = '/';
	}
	memcpy(path + n, key, key_len);
	n += key_len;
	memcpy(path + n, ".rasm", 5);
	n += 5;
	path[n] = '\0';
	path_normalize_slashes(path);
	return path;
}

static inline const char* concat_from_folder(const char* path, const char* end_path) { // TODO: Make all of these take String instead of const char*
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
	path_normalize_slashes(new_path);
	return new_path;
}
