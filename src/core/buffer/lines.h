#pragma once

#include "../../errors.h"
#include "../../settings.h"
#include "./chars.h"

#include <stdio.h>
#include <stdlib.h>
#include <str.h>
#include <strings.h>

typedef struct Lines {
	struct Lines *perv; // perv line
	size_t len; // content size

	Chars *start_ptr;
	Chars *end_ptr;

	size_t cap; // allocated size
	struct Lines *next; // next line
} Lines;

extern Lines *linesCreate();

extern void linesDestroy(Lines *line_ptr);

Chars *linesGetCharsByIndex(const Lines *const lines_ptr, const size_t index);
