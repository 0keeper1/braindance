#include "./layouts.h"

void writeHeaderBar( Core *const coreptr ) {}

void writeSideBars( Core *const coreptr ) {}

void writeFooterBar( Core *const coreptr ) {}

void writeCommandBar( Core *const coreptr ) {}

void writeContent( Core *const coreptr )
{
	Lines *cplinesptr = coreptr->lines;
	for ( ; cplinesptr != NULL; cplinesptr = cplinesptr->next )
	{
		windowbufAppend( &coreptr->window, cplinesptr->content, 80 );
	}
	return;
}

void writeLineNumber( Core *const coreptr ) {}