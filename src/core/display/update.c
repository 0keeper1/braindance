#include "./update.h"

Result display( Core *const coreptr )
{
	write( STDOUT_FILENO, SCREEN_CLEAR, 4 );

	writeHeaderBar( coreptr );
	writeFooterBar( coreptr );
	writeContent( coreptr );
	writeSideBars( coreptr );
	writeCommandBar( coreptr );

	windowbufWrite( &coreptr->window );

	return SUCCESSFUL;
}