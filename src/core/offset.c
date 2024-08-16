#include "./offset.h"

Offset offsetCreate()
{
	Offset offset = {
	    .cursor.cursoronchar = 0,
	    .cursor.cursoronline = 0,
	    .cursor.poscol = 0,
	    .cursor.posrow = 0,
	    .online = NULL,
	    .onchar = NULL,
	};
	return offset;
}