#pragma once

#include "./buffer/chars.h"
#include "./buffer/lines.h"
#include "./buffer/windowbuf.h"

struct Offset {
	struct Cursor {
		u_int16_t posrow;
		u_int16_t poscol;
	} cursor, promptcursor;

	Lines *online;
	Chars *onchar;
};

typedef struct Offset Offset;

extern Offset offsetCreate();

extern Result offsetInitialize(Offset *const offsetptr);
