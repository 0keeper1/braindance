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
	Lines *online;
	Chars *onchar;
};

typedef struct Offset Offset;

extern Offset offsetCreate();