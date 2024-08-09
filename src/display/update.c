#include "./update.h"

Result display( WindowBuf *const winbufptr, Offset *const offsetptr )
{
	writeHeaderBar();
	writeFooterBar();
	writeContent();
	writeSideBars();
	writeCommandBar();

	windowbufWrite( winbufptr );
	return SUCCESSFUL;
}