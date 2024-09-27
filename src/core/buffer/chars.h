#pragma once

#include "../../errors.h"
#include "../../settings.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

struct Chars {
	struct Chars *perv;
	char chr;
	struct Chars *next;
};

typedef struct Chars Chars;

extern Chars *charsConvertStringToChars(const char *ptr, const unsigned int len);

extern Chars *charsCreate(char chr);

extern void charsRemoveChar(Chars *chrptr);

extern void charsFree(Chars *chrptr);
