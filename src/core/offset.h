#pragma once

#include "./buffer/chars.h"
#include "./buffer/lines.h"
#include "./buffer/windowbuf.h"

struct Offset {
	struct Cursor {
		u_int16_t posrow;
		u_int16_t poscol;
	} cursor;

	struct Locations {
		u_int16_t header;
		u_int16_t footer;
		u_int16_t commandprompt;
	} locations;

	Lines *online;
	Chars *onchar;
};

typedef struct Offset Offset;

extern Offset offsetCreate();

extern Result offsetInitialize(Offset *const offsetptr);

extern Result offsetLocationsUpdate(Offset *const offsetptr, u_int16_t row, u_int16_t col);
