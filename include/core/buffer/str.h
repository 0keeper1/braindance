#pragma once

#include <stddef.h>

#include "../../errors.h"

typedef struct String {
	size_t len;
	char *ptr;
	size_t cap;
} String;

extern String *stringCreate();

extern Result stringAppend(String *string_ptr, const char chr);

extern String *stringToString(char *const ptr, const size_t len, const size_t cap);

extern void stringFree(String *string_ptr);
