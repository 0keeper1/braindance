#include "./update.h"

Result display( Core *const coreptr )
{
	write( STDOUT_FILENO, SCREEN_CLEAR, 4 );

	// WindowBuf *const winbuf = &coreptr->window;

	// writeHeaderBar( winbuf );
	// writeFooterBar( winbuf );
	// writeContent( winbuf );
	// writeSideBars( winbuf);
	// writeCommandBar(winbuf );

	// windowbufWrite( winbuf );

	return SUCCESSFUL;
}