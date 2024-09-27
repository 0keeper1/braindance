#pragma once

#include "str.h"
#include "../../errors.h"


typedef struct Chars {
	struct Chars *perv;
	char chr;
	struct Chars *next;
} Chars;

extern Chars *charsCreate(const char chr);

extern void charsFree(Chars *const chars_ptr);

extern Result charsRemoveAt(Chars *const chars_ptr);

extern Result charsRemove(Chars *chars_ptr);

extern Result charsAppend(Chars *chars_ptr, const char chr);

extern Result charsInsertAt(Chars *const chars_ptr, const char new_chr);

extern size_t charsLength(const Chars *chars_ptr);

extern Chars *charsGetEndPtr(Chars *const chars_ptr);

extern String *charsConvertCharsToString(const Chars *const chars_ptr);

extern Chars *charsConvertStringToChars(const String *string_ptr);
