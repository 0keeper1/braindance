#pragma once

#include <stddef.h>

#define STRING(name)                                                           \
	struct                                                                     \
	{                                                                          \
		size_t cap;                                                            \
		char* ptr;                                                             \
		size_t len;                                                            \
	} name
