#pragma once

#include "../../errors.h"
#include "../../settings.h"
#include "./chars.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

struct Lines {
	struct Lines *perv; // perv line
	unsigned int len; // content size
	union {
		char *content;
		Chars *chars;
	};

	unsigned int cap; // allocated size
	struct Lines *next; // next line
};

typedef struct Lines Lines;

extern void linesClear(Lines *lineptr);

extern void linesClearAndDrop(Lines *lineptr);

extern void linesDelete(Lines *lineptr);

extern char *linesContentCreate(int cap);

extern void linesSetContentPtr(Lines *lineptr, char *contentptr, int cap, int len);

extern void linesNewLine(Lines *lineptr);

extern Lines *linesCreate(char *contentptr, int cap, int len);

extern Lines *linesFileToLines(char *const pathptr);

extern Result linesClearAll(Lines *lineptr);

extern Result linesFree(Lines *lineptr);

extern Lines *linesReachEnd(Lines *lineptr);

extern Result linesDrop(Lines *lineptr);
