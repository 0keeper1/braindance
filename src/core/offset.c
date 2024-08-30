#include "./offset.h"

Offset offsetCreate()
{
	Offset offset = {
	    .cursor.poscol = 0,
	    .cursor.posrow = 0,
	    .online = NULL,
	    .onchar = NULL,
	};
	return offset;
}

Result offsetInitialize( Offset *const offsetptr, Lines *const linesptr )
{

	// offsetptr->online = linesptr;
	// offsetptr->onchar = charsConvertStringToChars();
	offsetptr->cursor.poscol = 0;
	offsetptr->cursor.posrow = 0;

	return SUCCESSFUL;
}