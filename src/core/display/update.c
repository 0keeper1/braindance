#include "./update.h"

Result display(Core *const coreptr) {
	WindowBuf winbuf = windowbufCreate();

	windowbufResize(&winbuf, coreptr->terminal.row, coreptr->terminal.col);

	windowbufAppend(&winbuf, SCREEN_CLEAR, 4);
	windowbufAppend(&winbuf, CURSOR_AT_START, 3);

	// writeHeaderBar(&winbuf);
	// writeFooterBar( coreptr );
	// writeContent( coreptr );
	// writeSideBars( coreptr );
	// writeCommandBar( coreptr );

	windowbufWrite(&winbuf);

	free(winbuf.ptr);

	return SUCCESSFUL;
}
