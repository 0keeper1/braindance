#pragma once

#include <stddef.h>

#include "core/buffer/chars.h"

typedef struct Prompt {
	Chars *start_ptr;
	size_t len;
	Chars *end_ptr;
} Prompt;

extern Prompt promptCreate();

extern void promptAppend(const Prompt *prompt_ptr, const char chr);
