#pragma once

#include <stddef.h>

#include "./chars.h"

typedef struct Lines {
	struct Lines *perv; // perv line

	Chars *start_ptr;
	size_t len; // content size
	Chars *end_ptr;

	struct Lines *next; // next line
} Lines;

extern Lines *linesCreate();

extern void linesDestroy(Lines *lines_ptr);

extern void linesAppend(Lines *lines_ptr);

extern Chars *linesGetCharsByIndex(const Lines *const lines_ptr, size_t index);

extern void linesInsertChars(Lines *lines_ptr, const size_t index, const char chr);

extern void linesDeleteChars(Lines *lines_ptr, const size_t index);
