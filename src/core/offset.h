#pragma once

#include "./buffer/chars.h"
#include "./buffer/lines.h"

struct Offset
{
	struct Cursor
	{
		u_int16_t posrow;
		u_int16_t poscol;
	} cursor;
	Lines *online;
	Chars *onchar;
};

typedef struct Offset Offset;

extern Offset offsetCreate();

extern Result offsetInitialize( Offset *const offsetptr, Lines *const linesptr );
