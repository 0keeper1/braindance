#include "./update.h"

Result display( WindowBuf *const winbufptr, Offset *const offsetptr, Lines *const lines )
{
	write( STDOUT_FILENO, SCREEN_CLEAR, 4 );

	writeHeaderBar( winbufptr );
	writeFooterBar( winbufptr );
	writeContent( winbufptr );
	writeSideBars( winbufptr );
	writeCommandBar( winbufptr );

	windowbufWrite( winbufptr );
	return SUCCESSFUL;
}