#pragma once

#include "./buffer/chars.h"
#include "./buffer/lines.h"

struct Offset
{
	struct Cursor
	{
		Chars *cursoronchar;
		Lines *cursoronline;
		int16_t posrow;
		int16_t poscol;
	} cursor;
};

typedef struct Offset Offset;

Offset const offsetCreate();