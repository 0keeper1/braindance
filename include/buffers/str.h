#pragma once

#include <stddef.h>

typedef struct Str
{
	size_t cap;
	char* ptr;
	size_t len;
} Str;
