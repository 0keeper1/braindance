#include "./offset.h"

Offset const offsetCreate()
{
	Offset offset = {
	    .cursor.cursoronchar = 0,
	    .cursor.cursoronline = 0,
	    .cursor.poscol = 0,
	    .cursor.posrow = 0,
	};
	Lines *online;
	Chars *onchar;
	return offset;
}