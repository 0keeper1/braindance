#pragma once

typedef struct Chars {
	struct Chars *perv;
	char chr;
	struct Chars *next;
} Chars;

extern Chars *charsCreate(const char chr);

extern void charsDestroy(Chars *chars);
