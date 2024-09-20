#include "./update.h"

Result display(const Core *const coreptr) {
	WindowBuf winbuf = windowbufCreate();

	windowbufResize(&winbuf, coreptr->terminal.row, coreptr->terminal.col);

	windowbufAppend(&winbuf, SCREEN_CLEAR, 4);
	windowbufAppend(&winbuf, CURSOR_AT_START, 3);

	writeHeaderBar(&winbuf, coreptr->terminal.col, coreptr->terminal.row);
	writeFooterBar(&winbuf, coreptr->terminal.col, coreptr->terminal.row);

	writeLineNumber(&winbuf, coreptr->terminal.row);
	writeCommandBar(&winbuf, coreptr->terminal.col, coreptr->terminal.row);

	windowbufWrite(&winbuf);

	free(winbuf.ptr);

	return SUCCESSFUL;
}
